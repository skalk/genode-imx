/*
 * \brief  VFS plugin interface implementation
 * \author Alice Domage
 * \date   2022-12-13
 */

#ifndef _VFS_SPI__SERVICE_H_
#define _VFS_SPI__SERVICE_H_

/* Genode includes */
#include <vfs/env.h>
#include <vfs/file_system.h>
#include <vfs/single_file_system.h>

/* Local includes */
#include "spi_gpio_device.h"
#include "bytefifo.h"

namespace Vfs_spi {

	using namespace Genode;
	using namespace Vfs;

	class Spi_file_system;
}

class Vfs_spi::Spi_file_system: public Single_file_system
{
private:
	Xml_node _node;

	class Spi_handle: public Single_vfs_handle
	{
	private:
		Allocator& _alloc;
		Byte_fifo _rx_fifo { _alloc, 32 };
		Spi_gpio::Device& _device;
		uint8_t _tx_buffer[32];
		uint8_t _rx_buffer[32];

		/*
		 * Noncopyable
		 */
		Spi_handle(Spi_handle const &);
		Spi_handle &operator = (Spi_handle const &);

	public:

		Spi_handle(Directory_service &ds,
		           File_io_service   &fs,
		           Genode::Allocator &alloc,
		           Spi_gpio::Device& device)
		: Single_vfs_handle(ds, fs, alloc, 0), _alloc(alloc), _device(device)
		{
		}

		Read_result read(Byte_range_ptr const &dst, size_t &out_count) override
		{
			size_t bytes = Genode::min(dst.num_bytes, _rx_fifo.available());
			for (size_t i = 0; i < bytes; i++) {
				dst.start[i] = _rx_fifo.dequeue();
			}
			out_count = bytes;
			return Read_result::READ_OK;
		}

		Write_result write(Const_byte_range_ptr const &src, size_t &out_count) override
		{
			size_t remaining = src.num_bytes;
			uint8_t const* current = reinterpret_cast<uint8_t const*>(src.start);
			while (remaining > 0) {
				size_t bytes = Genode::min(sizeof(_rx_buffer), remaining);
				_device.transfer(current, _rx_buffer, bytes);
				for (size_t i = 0; i < bytes; i++) {
					_rx_fifo.enqueue(_rx_buffer[i]);
				}
				remaining -= bytes;
				current += bytes;
			}
			out_count = src.num_bytes;
			return Write_result::WRITE_OK;
		}

		bool read_ready()  const override
		{
			return _rx_fifo.available() > 0;
		}

		bool write_ready() const override
		{
			return (_rx_fifo.length() - _rx_fifo.available()) > 0;
		}
	};

	Spi_gpio::Device *_device { nullptr };
	Vfs::Env &_env;

public:
	/**
	 * Constructor
	 *
	 * The 'config' XML node (that points to its content) is stored within
	 * the object after construction time. The underlying backing store
	 * must be kept in tact during the lifefile of the object.
	 */
	Spi_file_system(Vfs::Env& vfs_env, Genode::Xml_node config)
	:
		Single_file_system(Vfs::Node_type::TRANSACTIONAL_FILE, name(),
						   Node_rwx::rw(), config),
		_node   { config },
		_env    { vfs_env }
	{
	}

	Spi_file_system(Spi_file_system const &) = delete;
	Spi_file_system &operator=(Spi_file_system const &) = delete;

	static char const *name()   { return "spi"; }
	char const *type() override { return "spi"; }

	/********************************
	 ** Directory service interface **
	 ********************************/

	Open_result open(char const  *path, unsigned,
					 Vfs_handle **out_handle,
					 Allocator   &alloc) override
	{
		if (!_device) {
			_device = new (alloc) Spi_gpio::Device(_env, alloc, _node);
		}

		if (!_single_file(path)) {
			return OPEN_ERR_UNACCESSIBLE;
		}

		try {
			*out_handle = new (alloc) Spi_handle(*this, *this, alloc, *_device);
			return OPEN_OK;
		}
		catch (Genode::Out_of_ram)  { return OPEN_ERR_OUT_OF_RAM; }
		catch (Genode::Out_of_caps) { return OPEN_ERR_OUT_OF_CAPS; }
	}

	Stat_result stat(char const *path, Stat &out) override
	{
			Stat_result const result = Single_file_system::stat(path, out);
			out.size = 0;
			return result;
	}
};

#endif /* _VFS_SPI__SERVICE_H_ */
