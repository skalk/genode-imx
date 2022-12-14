/*
 * \brief  SPI/GPIO device
 * \author Stefan Thoeni <stefan.thoeni@gapfruit.com>
 * \date   2022-12-16
 */

/*
 * Copyright (C) 2022-2023 Genode Labs GmbH
 * Copyright (C) 2021-2022 gapfruit AG
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__SPI_GPIO_DEVICE_H_
#define _INCLUDE__SPI_GPIO_DEVICE_H_

/* Genode includes */
#include <gpio_session/connection.h>
#include <timer_session/connection.h>
#include <util/reconstructible.h>

/* Local includes */
#include "spi_driver.h"

namespace Spi_gpio {
	class Device;

	using Genode::uint8_t;
	using Genode::uint16_t;
	using Genode::uint32_t;
	using Genode::size_t;
}

class Spi_gpio::Device {
	private:
		Vfs::Env& _env;
		Genode::Allocator& _alloc;
		Genode::Xml_node& _config;
		uint16_t const _burst_size  = 32;
		bool const _byte_reordering = true;
		Spi::Driver& _driver { *Spi::initialize(_env, _config) };
		Timer::Connection _timer { _env.env() };
		Genode::Constructible<Gpio::Connection> _slave_select { };
		Genode::Constructible<Gpio::Connection> _reset { };
		uint32_t const _reset_delay { _config.attribute_value("reset_delay", 0u) };
		uint32_t const _guard_delay { _config.attribute_value("guard_delay", 0u) };
		uint32_t const _assert_delay { _config.attribute_value("assert_delay", 0u) };

		void _reset_device();

		void _assert_slave_select();

		void _deassert_slave_select();

	public:
		void transfer(uint8_t const* tx_buffer, uint8_t* rx_buffer, size_t buffer_size);

		Device(Vfs::Env& env, Genode::Allocator& alloc, Genode::Xml_node config);
};

#endif /* _INCLUDE__SPI_GPIO_DEVICE_H_ */

