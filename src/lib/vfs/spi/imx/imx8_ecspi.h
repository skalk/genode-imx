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

#ifndef _INCLUDE__IMX8_ECSPI__DRIVER_H_
#define _INCLUDE__IMX8_ECSPI__DRIVER_H_

/* Genode includes */
#include <base/env.h>
#include <base/semaphore.h>
#include <irq_session/client.h>
#include <os/ring_buffer.h>
#include <platform_session/connection.h>
#include <timer_session/connection.h>
#include <util/xml_node.h>

/* Local includes */
#include "spi_driver.h"
#include "imx8_ecspi_mmio.h"

namespace Spi {
	using namespace Genode;

	class Ecspi_driver;
}


class Spi::Ecspi_driver : public Spi::Driver {
public:

	struct Config {
		bool     verbose       = false;
		bool     loopback      = false;
		uint8_t  clock_divider = 0;
		uint64_t timeout       = 1000; /* in millisecond */
	};


private:

	class Timeout {
	private:

		Timer::Connection _timer;

		friend Timer::One_shot_timeout<Timeout>;
		Timer::One_shot_timeout<Timeout> _timeout { _timer, *this, &Timeout::_handler };

		volatile bool _reached { false };

		void _handler(Genode::Duration) {
			_reached = true;
		}

	public:

		Timeout(Genode::Env &env)
		: _timer { env }
		{}

		void discard() { _timeout.discard(); }

		bool reached() { return _reached; }

		void schedule_ms(size_t milliseconds)
		{
			discard();
			_reached  = false;
			_timeout.schedule(Genode::Microseconds { milliseconds * 1000 });
		}

	};


private:

	Genode::Env &_env;
	Timeout      _bus_timeout { _env };
	const Config _config;

	/* platform connection */
	Platform::Connection _platform { _env };
	Platform::Device     _device   { _platform };

	/* iomem */
	Spi::Mmio _mmio       { _device };

	/* driver state */
	enum State {
		IDLE,
		TRANSMITTING
	};

	State _state { State::IDLE };

	/* interrupt handler */
	Platform::Device::Irq           _irq { _device };
	Io_signal_handler<Ecspi_driver> _irq_handler;

	void _irq_handle();

	struct Transfer {

		static constexpr size_t MAX_BURST_SIZE = 256;

		uint8_t *buffer      = nullptr;
		size_t   buffer_size = 0;
		size_t   tx_bytes    = 0;
		size_t   rx_bytes    = 0;
	};

	void _bus_enable(Settings const &settings, uint8_t slave_select);

	void _bus_disable();

	void _bus_exchange(Bus_transaction &transaction);

	void _bus_execute_transaction();

	size_t _fifo_write(uint8_t const *buffer, size_t size, bool byte_reordering);

	size_t _fifo_read_unaligned(uint8_t *buffer, size_t size, bool byte_reordering);

	size_t _fifo_read(uint8_t *buffer, size_t size, bool byte_reordering);

	inline uint32_t _word_swap_u32(uint32_t word) const
	{
		/* [0x04, 0x03, 0x02, 0x01] -> [0x01, 0x02, 0x03, 0x04] */
		return ((word>>24)&0xff)    |
		       ((word<<8)&0xff0000) |
		       ((word>>8)&0xff00)   |
		       ((word<<24)&0xff000000);
	}

	inline uint32_t _word_swap_u24(uint32_t word) const
	{
		/* [XX, 0x03, 0x02, 0x1] -> [XX, 0x01, 0x02, 0x03] */
		return ((word << 16) & 0xFF0000) |
		       (word & 0x00FF00)         |
		       ((word >> 16) & 0x0000FF);
	}

	inline uint32_t _word_swap_u16(uint32_t word) const
	{
		/* [XX, XX 0x02, 0x01] -> [XX, XX, 0x01, 0x02] */
		return ((word >> 8) & 0xFF) | ((word << 8) & 0xFF00);
	}

	inline uint32_t _byte_reordering(uint32_t word, size_t byte_count = 4) const
	{
		if (byte_count == 4) {
			return _word_swap_u32(word);
		} else if (byte_count == 3) {
			return _word_swap_u24(word);
		} else if(byte_count == 2) {
			return _word_swap_u16(word);
		}
		return word;
	}

public:

	explicit Ecspi_driver(Ecspi_driver const&)          = delete;
	Ecspi_driver const &operator=(Ecspi_driver const &) = delete;

	Ecspi_driver(Genode::Env &env, Config const &config)
	:
		_env { env },
		_config { config },
		_irq_handler { _env.ep(), *this, &Ecspi_driver::_irq_handle }
	{
		_irq.sigh(_irq_handler);
		_irq_handle();
		_irq.ack();
	}

	void transfer(Bus_transaction& trxn) override;
};

#endif // _INCLUDE__IMX8_ECSPI__DRIVER_H_

