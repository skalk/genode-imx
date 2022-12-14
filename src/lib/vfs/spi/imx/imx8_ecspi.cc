/*
 * \brief  Ecspi driver for imx8 based SoC
 * \author Alice Domage
 * \date   2022-12-15
 */

/*
 * Copyright (C) 2013-2022 Genode Labs GmbH
 * Copyright (C) 2021-2022 gapfruit AG
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Local include */
#include "imx8_ecspi.h"

/******************
 ** Irq Handling **
 *****************/

void Spi::Ecspi_driver::_irq_handle()
{

	if (_mmio.read<Mmio::Status::Tx_fifo_full>()) {
		if (_config.verbose) {
			Genode::log("Tx FIFO is full.");
		}
	}

	if (_mmio.read<Mmio::Status::Rx_fifo_full>()) {
		if (_config.verbose) {
			Genode::log("Rx FIFO is full.");
		}
	}

	/* we don't want that to happen */
	if (_mmio.read<Mmio::Status::Rx_fifo_overflow>()) {
		Genode::error("Rx FIFO overflow, data loss!");
		/* rx_overflow must be cleared. Reset value = 1 */
		_mmio.write<Mmio::Status::Rx_fifo_overflow>(1);
	}

	if (_mmio.read<Mmio::Status::Rx_fifo_ready>()) {
		if (_config.verbose) {
			Genode::log("Rx FIFO is ready.");
		}
	}

	if (_mmio.read<Mmio::Status::Tx_complete>()) {
		if (_config.verbose) {
			Genode::log("Tx transaction completed.");
		}
		/* tx_complete must be cleared. Reset value = 1 */
		_mmio.write<Mmio::Status::Tx_complete>(1);
		_state = State::IDLE;
	}

	_irq.ack();
}


/******************
 * Bus operations *
 ******************/

void Spi::Ecspi_driver::_bus_enable(Settings const &settings, uint8_t slave_select)
{
	/* enable SPI chipset, note on imx8q only ss: 0 is available */
	_mmio.write<Mmio::Control::Enable>(1);

	/* set master mode on the selected slave */
	_mmio.write<Mmio::Control::Channel_select>(slave_select);
	_mmio.write<Mmio::Control::Channel_mode>( 1 << slave_select);

	/* configure loopback mode if needed */
	if (_config.loopback) {
		_mmio.write<Mmio::Test::Loop_back_ctl>(1);
		/* use full FIFO size */
		_mmio.write<Mmio::Test::Rx_fifo_counter>(0xFF);
		_mmio.write<Mmio::Test::Tx_fifo_counter>(0xFF);
	}

	/* configure clock divider and line */
	_mmio.write<Mmio::Control::Pre_divider>(_config.clock_divider >> 4);
	_mmio.write<Mmio::Control::Post_divider>(_config.clock_divider & 0xF);
	_mmio.write<Mmio::Config::Clock_phase>((settings.mode & 0x1) << slave_select);
	_mmio.write<Mmio::Config::Clock_polarity>((settings.mode & 0x2) << slave_select);
	_mmio.write<Mmio::Config::Clock_idle_state>(settings.clock_idle_state << slave_select);

	/* configure data lines idle state */
	_mmio.write<Mmio::Config::Data_idle_state>(settings.data_lines_idle_state << slave_select);

	/* configure slave select active state */
	_mmio.write<Mmio::Config::Slave_select_polarity>(settings.ss_line_active_state << slave_select);

	/* enable interrupt */
	_mmio.write<Mmio::Interrupt::Tx_completed_enable>(1);
}


void Spi::Ecspi_driver::_bus_disable()
{
	_mmio.write<Mmio::Control>(0);
}


void Spi::Ecspi_driver::_bus_execute_transaction()
{

	/* set the exchange bit which tell the hardware to start executing the transaction */
	_state = State::TRANSMITTING;
	_mmio.write<Mmio::Control::Exchange>(1);

	_bus_timeout.schedule_ms(_config.timeout);

	/* wait the Tx_complete irq to notify us */
	while (_state == State::TRANSMITTING) {
		if (_bus_timeout.reached()) {
			_state = State::IDLE;
			_bus_disable();
			error("Bus timeout");
			throw Spi::Bus_error();
		}

		/*
		 * Depending on how many Irq we have enabled, it is possible to receive multiple of them
		 * before the transaction is fully completed.
		 */
		_env.ep().wait_and_dispatch_one_io_signal();
	}

	/*
	 * From the platform specification the transfer might not be fully completed even after receiving
	 * the Tx_complete irq. We must poll the exchange bit to make sure the transaction is terminated.
	 */
	_bus_timeout.schedule_ms(_config.timeout);
	while (_mmio.read<Mmio::Control::Exchange>()) {
		if (_bus_timeout.reached()) {
			_bus_disable();
			error("Bus timeout");
			throw Spi::Bus_error();
		}
	}

	_bus_timeout.discard();
}


void Spi::Ecspi_driver::_bus_exchange(Bus_transaction &trxn)
{
	/* exchange as many burst that it is needed to send the buffer provided by the client */
	while (trxn.tx_offset < trxn.buffer_size) {
		size_t const remaining_bytes = trxn.buffer_size - trxn.tx_offset;

		/* align the next transfer on the maximum burst size */
		uint16_t const burst_size = static_cast<uint16_t>(remaining_bytes % trxn.max_burst_size ?
		                                                  remaining_bytes % trxn.max_burst_size :
		                                                  trxn.max_burst_size);

		_mmio.write<Mmio::Control::Burst_length>((burst_size * 8) - 1);

		/* write burst_size of the buffer to the tx FIFO */
		trxn.tx_offset += _fifo_write(trxn.tx_buffer + trxn.tx_offset, burst_size, trxn.byte_reordering);

		/* execute the transaction */
		_bus_execute_transaction();

		/* Read received bytes during the transfer from the rx FIFO */
		trxn.rx_offset += _fifo_read(trxn.rx_buffer + trxn.rx_offset, burst_size, trxn.byte_reordering);

		/* if an incoherence happen, less byte are read than written, abort the transaction */
		if (trxn.tx_offset != trxn.rx_offset) {
			Genode::error("Transaction failed because of a tx/rx FIFO read incoherence.");
			throw Spi::Bus_error();
		}
	}
}


/*******************
 * FIFO operations *
 *******************/

Genode::size_t Spi::Ecspi_driver::_fifo_write(uint8_t const *buffer, size_t size, bool byte_reodering)
{
	size_t bytes_count = 0;

	size_t const unaligned_bytes = size % sizeof(uint32_t);

	/* unaligned bytes might be */
	if (unaligned_bytes) {
		uint32_t word = *reinterpret_cast<uint32_t const *>(buffer);
		if (byte_reodering) {
			word = _byte_reordering(word, unaligned_bytes);
		}
		_mmio.write<Mmio::Data_tx>(word);
		bytes_count += unaligned_bytes;
	}

	/* write the rest of the buffer content aligned on word */
	while (bytes_count < size) {
		uint32_t word = *reinterpret_cast<int32_t const *>(buffer + bytes_count);
		if (byte_reodering) {
			word = _byte_reordering(word);
		}
		_mmio.write<Mmio::Data_tx>(word);
		bytes_count += sizeof(uint32_t);
	}

	return bytes_count;
}


Genode::size_t Spi::Ecspi_driver::_fifo_read_unaligned(uint8_t *buffer, size_t size, bool byte_reordering)
{
	size_t const unaligned_bytes = size % sizeof(uint32_t);

	if (unaligned_bytes && _mmio.read<Mmio::Status::Rx_fifo_ready>()) {
		uint32_t word = _mmio.read<Mmio::Data_rx>();
		if (byte_reordering) {
			word = _byte_reordering(word, unaligned_bytes);
		}
		memcpy(buffer, &word, unaligned_bytes);
	}
	return unaligned_bytes;
}


Genode::size_t Spi::Ecspi_driver::_fifo_read(uint8_t *buffer, size_t size, bool byte_reordering)
{
	size_t bytes_count = 0;

	bytes_count += _fifo_read_unaligned(buffer, size, byte_reordering);
	while (_mmio.read<Mmio::Status::Rx_fifo_ready>()) {
		if (bytes_count >= size) { throw Spi::Bus_error(); }
		uint32_t word = _mmio.read<Mmio::Data_rx>();
		if (byte_reordering) {
			word = _byte_reordering(word);
		}
		*reinterpret_cast<uint32_t*>(buffer + bytes_count) = word;
		bytes_count += sizeof(uint32_t);
	}
	return bytes_count;
}


/************
 * Transfer *
 ************/

void Spi::Ecspi_driver::transfer(Bus_transaction &trxn)
{
	if (trxn.slave_select != 0) {
		error("Only native slave select 0 is supported. Use GPIO for multiple device.");
		throw Spi::Bus_error();
	}
	if (trxn.max_burst_size > 256) {
		error("Local implementation support burst size up to 256, ", trxn.max_burst_size, " asked.");
		throw Spi::Bus_error();
	}

	if (_config.verbose) {
		log("Begin transaction with ", trxn.buffer_size, " bytes.");
		log("Session bus settings:");
		log("\tslave_select: ", trxn.slave_select);
		log("\tmode: ", Hex { trxn.settings.mode });
		log("\t\tclk_polarity: ", Hex { trxn.settings.mode & 0x1 });
		log("\t\tclk_phase: ", Hex { trxn.settings.mode & 0x2 });
		log("\tclock_idle_state: ", Hex { trxn.settings.clock_idle_state });
		log("\tss_line_active_state: ", Hex { trxn.settings.ss_line_active_state });
	}

	/* enable the Spi bus with the client session settings */
	_bus_enable(trxn.settings, trxn.slave_select);

	try {
		/* execute the transfer */
		_bus_exchange(trxn);
	} catch (...) {
		_bus_disable();
		throw;
	}

	_bus_disable();
}


/*
 * Required by spi_driver.h
 */

Spi::Ecspi_driver::Config Parse_ecspi_config(Genode::Xml_node const &node) {
	return {
		.verbose       = node.attribute_value("verbose", false),
		.loopback      = node.attribute_value("loopback", false),
		.clock_divider = node.attribute_value("clock_divider", static_cast<Genode::uint8_t>(0)),
		.timeout       = node.attribute_value("timeout", static_cast<Genode::uint64_t>(1000)),
	};
}

/*
 * On Imx8q_evk only ecspi with FIFO based transfer is implemented.
 * Update the initializer with new implementation (e.g ecspi with dma transfer, or qspi)
 * allocated based on the config.
 */
Spi::Driver* Spi::initialize(Vfs::Env &vfs_env, const Xml_node &node) {
	auto config = Parse_ecspi_config(node);
	auto *driver = new (vfs_env.alloc()) Ecspi_driver { vfs_env.env(), config };
	return reinterpret_cast<Spi::Driver*>(driver);
}

