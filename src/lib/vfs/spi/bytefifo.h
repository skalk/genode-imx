/*
 *  \brief  Fifo of bytes
 *  \author Stefan Thoeni
 *  \date   2022-12-20
 */

#ifndef _VFS_SPI__BYTEFIFO_H_
#define _VFS_SPI__BYTEFIFO_H_

/* Genode includes */
#include <vfs/env.h>
#include <vfs/file_system.h>
#include <vfs/single_file_system.h>

/* Local includes */
#include "spi_gpio_device.h"

namespace Vfs_spi {

	using namespace Genode;

	class Byte_fifo;
	class Fifo_underrun : public Exception { };
}

class Vfs_spi::Byte_fifo
{
private:
	Allocator& _alloc;
	size_t _length;
	uint8_t* _buffer;
	uint8_t* _first;
	uint8_t* _next;

public:
	Byte_fifo(Allocator& alloc, size_t initial_length)
	 : _alloc(alloc),
	   _length(initial_length),
	   _buffer(static_cast<uint8_t*>(_alloc.alloc(_length))),
	   _first(_buffer),
	   _next(_buffer)
	{
	}

	~Byte_fifo()
	{
		_alloc.free(_buffer, _length);
	}

	size_t length() const
	{
		return _length;
	}

	size_t available() const
	{
		return static_cast<size_t>(_next - _first);
	}

	void enqueue(uint8_t value)
	{
		if (_next >= (_buffer + _length)) {
			size_t avail = available();
			size_t new_length = avail > (_length / 2) ? (_length * 2) : _length;
			uint8_t* new_buffer = static_cast<uint8_t*>(_alloc.alloc(new_length));
			Genode::memcpy(new_buffer, _first, avail);
			_first = new_buffer;
			_next = new_buffer + avail;
			_alloc.free(_buffer, _length);
			_buffer = new_buffer;
			_length = new_length;
		}

		*_next = value;
		_next++;
	}

	uint8_t dequeue()
	{
		if (available() < 1)
			throw Fifo_underrun();

		uint8_t value = *_first;
		_first++;
		return value;
	}

	Byte_fifo(Byte_fifo const &) = delete;
	Byte_fifo &operator=(Byte_fifo const &) = delete;
};

#endif /* _VFS_SPI__BYTEFIFO_H_ */
