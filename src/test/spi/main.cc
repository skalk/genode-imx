/*
 * \brief  Test spi driver with a shift register
 * \author Jean-Adrien Domage <jean-adrien.domage@gapfruit.com>
 * \date   2021-04-28
 */

/*
 * Copyright (C) 2013-2024 Genode Labs GmbH
 * Copyright (C) 2021 gapfruit AG
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* std includes */
#include <cstring>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <vector>

namespace Spi {
	struct Assertion_failed {};

	constexpr char const * device = "/dev/shiftregister";
}


#define ASSERT_NE(a, b) \
{ \
	if (a == b) { \
		std::cout << "Assertion failed on line: " << __LINE__ << std::endl; \
		throw Spi::Assertion_failed(); \
	} \
}


#define ASSERT_EQ(a, b) \
{ \
	if (a != b) { \
		std::cout << "Assertion failed on line: " << __LINE__ << std::endl; \
		throw Spi::Assertion_failed(); \
	} \
}


static void shiftregister_device_exposure()
{
	DIR           *dir;
	struct dirent *dir_entry;

	dir = opendir("/dev");
	ASSERT_NE(dir, nullptr);

	dir_entry = readdir(dir);
	ASSERT_EQ(std::strcmp(dir_entry->d_name, "shiftregister"), 0);
	closedir(dir);
}

static void shiftregister_small_label()
{
	static constexpr char const small_label[] = { "Hello friend!" };
	char buffer[sizeof(small_label)] = { "" };
	
	std::fstream device { Spi::device };
	ASSERT_EQ(device.is_open(), true);

	device.write(small_label, sizeof(small_label));
	device.read(buffer, sizeof(buffer));
	std::cout << small_label << std::endl;
	std::cout << buffer << std::endl;
	ASSERT_EQ(std::strcmp(small_label, buffer), 0);

	device.close();
	ASSERT_NE(device.is_open(), true);
}


int main(int, char **)
{
	std::cout << "SPI test started ... " <<  std::endl;
	shiftregister_device_exposure();
	shiftregister_small_label();
	std::cout << "SPI shift register test succeed!" <<  std::endl;
}
