/*
 * \brief  SPI driver base class to be implemented by platform specific 
 * \author Alice Domage
 * \date   2022-12-12
 */

/*
 * Copyright (C) 2013-2022 Genode Labs GmbH
 * Copyright (C) 2021-2022 gapfruit AG
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__SPI_DRIVER__INTERFACE_H_
#define _INCLUDE__SPI_DRIVER__INTERFACE_H_

/* Genode includes */
#include <vfs/env.h>
#include <util/xml_node.h>

/* Os include */

namespace Spi {

	using namespace Genode;
	class Driver;
	struct Settings;

	class Bus_error : public Exception { };

	Driver* initialize(Vfs::Env &env, Xml_node const &config);
}

/**
 * Spi settings
 *
 * This struct is use to control the bus settings at a session level.
 */
struct Spi::Settings {

	enum {
		STATE_HIGH = 1,
		STATE_LOW  = 0,
	};

	/*
	 * Spi mode are as follow:
	 *  - MODE 0 (value 0): clk line POLARITY: 0 PHASE: 0
	 *  - MODE 1 (value 1): clk line POLARITY: 0 PHASE: 1
	 *  - MODE 2 (value 2): clk line POLARITY: 1 PHASE: 0
	 *  - MODE 3 (value 3): clk line POLARITY: 1 PHASE: 1
	 */
	uint32_t mode:                      2;

	/*
	 * Spi clock idle state control. This control if the clock must
	 * stay HIGH or stay LOW while it is idle
	 */
	uint32_t clock_idle_state:          STATE_HIGH;

	/*
	 * Spi data lines state control. This control if the clock must
	 * stay HIGH or stay LOW while it is idle
	 */
	uint32_t data_lines_idle_state:     STATE_HIGH;

	/*
	 * Spi slave select line active state, determinate which state has to be
	 * considered the active state.
	 */
	uint32_t ss_line_active_state:      STATE_HIGH;
};

/*
 * Base class for platform specific driver to implement
 *
 * Note about the endianness: the driver is transparent.
 *
 * The driver read/write bytes to memory in the order they are
 * read/write to the bus.
 * It is the responsibility of the component interacting with
 * a slave device on the bus to figure out how to interpret the data. 
 */
class Spi::Driver : Interface
{
public:
	/* Spi bus transaction */
	struct Bus_transaction {
		Settings       settings        = { }; /* Client session setting */
		uint8_t        slave_select    = 0;   /* Slave select line. */
		uint16_t       max_burst_size  = 8;
		bool           byte_reordering = true;
		uint8_t const *tx_buffer       = nullptr;
		uint8_t       *rx_buffer       = nullptr;
		size_t         tx_offset       = 0; /* used by driver implementation */
		size_t         rx_offset       = 0; /* used by driver implementation */
		size_t         buffer_size     = 0;
	};


	/*
	 * Execute an Spi transaction
	 *
	 * \details The data provided threw the transaction buffer is read to transmit data. The received data are
	 * directly copied into that same buffer.
	 * \attention This methode is NOT thread safe
	 *
	 * \param trxn transaction to execute
	 * \return the received bytes count
	 */
	virtual void transfer(Bus_transaction& trxn) = 0;
};

#endif /* _INCLUDE__SPI_DRIVER__INTERFACE_H_ */

