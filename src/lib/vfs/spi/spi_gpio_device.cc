/* Genode includes */
#include "spi_gpio_device.h"

Spi_gpio::Device::Device(Vfs::Env& env, Genode::Allocator& alloc, Genode::Xml_node config)
 : _env(env), _alloc(alloc), _config(config)
{
	constexpr uint32_t invalid_gpio_line = 0xffffffff;
	uint32_t slave_select_line = _config.attribute_value("slave_select_gpio", invalid_gpio_line);
	uint32_t reset_line = _config.attribute_value("reset_gpio", invalid_gpio_line);

	if (slave_select_line < invalid_gpio_line) {
		_slave_select.construct(_env.env(), slave_select_line);
	}

	if (reset_line < invalid_gpio_line) {
		_reset.construct(_env.env(), reset_line);
	}

	_reset_device();
}

void Spi_gpio::Device::_reset_device()
{
	if (_reset.constructed()) {
		_reset->write(false);
		if (_reset_delay > 0) {
			_timer.usleep(_reset_delay);
		}
		_reset->write(true);
		if (_guard_delay > 0) {
			_timer.usleep(_guard_delay);
		}
	}
}

void Spi_gpio::Device::_assert_slave_select()
{
	if (_slave_select.constructed()) {
		_slave_select->write(false);
		if (_assert_delay > 0) {
			_timer.usleep(_assert_delay);
		}
	}
}

void Spi_gpio::Device::_deassert_slave_select()
{
	if (_slave_select.constructed()) {
		_slave_select->write(true);
		if (_assert_delay > 0) {
			_timer.usleep(_assert_delay);
		}
	}
}

void Spi_gpio::Device::transfer(uint8_t const* tx_buffer, uint8_t* rx_buffer, size_t buffer_size)
{
	Spi::Settings settings {
		.mode = 0,
		.clock_idle_state = 0,
		.data_lines_idle_state = 0,
		.ss_line_active_state = 0,
	};
	Spi::Driver::Bus_transaction transaction {
		.settings        = settings,
		.slave_select    = 0,
		.max_burst_size  = _burst_size,
		.byte_reordering = _byte_reordering,
		.tx_buffer       = tx_buffer,
		.rx_buffer       = rx_buffer,
		.buffer_size     = buffer_size,
	};
	_assert_slave_select();
	_driver.transfer(transaction);
	_deassert_slave_select();
}

