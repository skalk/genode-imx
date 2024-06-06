/*
 * \brief  IOMUX controller for i.MX8MP
 * \author Stefan Kalkowski
 * \date   2024-06-08
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef __PLATFORM__IMX__IOMUXC_H_
#define __PLATFORM__IMX__IOMUXC_H_

#include <os/attached_mmio.h>

namespace Driver {
	using namespace Genode;

	struct Iomuxc;
};


/* The following values are taken from device-tree sources of the
 * vendor from their Linux kernel forks, therefore they have this
 * specific form of arrays:
 */
enum Indices {
	MUX_REG, CONF_REG, INPUT_REG, MUX_MODE, INPUT_VAL, CONF_VAL, MAX };

static Genode::uint32_t pinctrl_setting [][MAX] {
	/* pinctrl_ie_di4o4 */
	{ 0x1d4, 0x434, 0x000, 0x5, 0x0, 0x00  },
	{ 0x1c8, 0x428, 0x000, 0x5, 0x0, 0x00  },
	{ 0x1c4, 0x424, 0x000, 0x5, 0x0, 0x00  },
	{ 0x1bc, 0x41c, 0x000, 0x5, 0x0, 0x00  },
	{ 0x1c0, 0x420, 0x000, 0x5, 0x0, 0x100 },
	{ 0x1d8, 0x438, 0x000, 0x5, 0x0, 0x100 },
	{ 0x018, 0x278, 0x000, 0x0, 0x0, 0x100 },
	{ 0x178, 0x3d8, 0x000, 0x5, 0x0, 0x100 },

	/* pinctrl_usdhc3_200mhz */
	{ 0x124, 0x384, 0x604, 0x2, 0x1, 0x196 },
	{ 0x128, 0x388, 0x60c, 0x2, 0x1, 0x1d6 },
	{ 0x108, 0x368, 0x610, 0x2, 0x1, 0x1d6 },
	{ 0x10c, 0x36c, 0x614, 0x2, 0x1, 0x1d6 },
	{ 0x110, 0x370, 0x618, 0x2, 0x1, 0x1d6 },
	{ 0x114, 0x374, 0x61c, 0x2, 0x1, 0x1d6 },
	{ 0x11c, 0x37c, 0x620, 0x2, 0x1, 0x1d6 },
	{ 0x0ec, 0x34c, 0x624, 0x2, 0x1, 0x1d6 },
	{ 0x0f0, 0x350, 0x628, 0x2, 0x1, 0x1d6 },
	{ 0x0f4, 0x354, 0x62c, 0x2, 0x1, 0x1d6 },
	{ 0x0e8, 0x348, 0x630, 0x2, 0x1, 0x196 },

	/* pinctrl_fec */
	{ 0x08c, 0x2ec, 0x000, 0x1, 0x0, 0x3  },
	{ 0x090, 0x2f0, 0x57c, 0x1, 0x0, 0x3  },
	{ 0x09c, 0x2fc, 0x580, 0x1, 0x0, 0x91 },
	{ 0x0a0, 0x300, 0x584, 0x1, 0x0, 0x91 },
	{ 0x168, 0x3c8, 0x000, 0x4, 0x0, 0x91 },
	{ 0x16c, 0x3cc, 0x000, 0x4, 0x0, 0x91 },
	{ 0x174, 0x3d4, 0x000, 0x4, 0x0, 0x91 },
	{ 0x170, 0x3d0, 0x588, 0x4, 0x1, 0x91 },
	{ 0x098, 0x2f8, 0x000, 0x1, 0x0, 0x1f },
	{ 0x094, 0x2f4, 0x000, 0x1, 0x0, 0x1f },
	{ 0x180, 0x3e0, 0x000, 0x4, 0x0, 0x1f },
	{ 0x184, 0x3e4, 0x000, 0x4, 0x0, 0x1f },
	{ 0x188, 0x3e8, 0x000, 0x4, 0x0, 0x1f },
	{ 0x18c, 0x3ec, 0x000, 0x4, 0x0, 0x1f },

	/* pinctrl_eqos */
	{ 0x054, 0x2b4, 0x000, 0x0, 0x0, 0x3  },
	{ 0x058, 0x2b8, 0x590, 0x0, 0x1, 0x3  },
	{ 0x07c, 0x2dc, 0x000, 0x0, 0x0, 0x91 },
	{ 0x080, 0x2e0, 0x000, 0x0, 0x0, 0x91 },
	{ 0x084, 0x2e4, 0x000, 0x0, 0x0, 0x91 },
	{ 0x088, 0x2e8, 0x000, 0x0, 0x0, 0x91 },
	{ 0x078, 0x2d8, 0x000, 0x0, 0x0, 0x91 },
	{ 0x074, 0x2d4, 0x000, 0x0, 0x0, 0x91 },
	{ 0x068, 0x2c8, 0x000, 0x0, 0x0, 0x1f },
	{ 0x064, 0x2c4, 0x000, 0x0, 0x0, 0x1f },
	{ 0x060, 0x2c0, 0x000, 0x0, 0x0, 0x1f },
	{ 0x05c, 0x2bc, 0x000, 0x0, 0x0, 0x1f },
	{ 0x06c, 0x2cc, 0x000, 0x0, 0x0, 0x1f },
	{ 0x070, 0x2d0, 0x000, 0x0, 0x0, 0x1f },

	/* pinctrl_i2c2 */
	{ 0x208, 0x468, 0x5ac, 0x0, 0x2, 0x400001c3 },
	{ 0x20c, 0x46c, 0x5b0, 0x0, 0x2, 0x400001c3 },

	/* pinctrl_wdog */
	{ 0x01c, 0x27c, 0x000, 0x1, 0x0, 0xc6 }
};


struct Driver::Iomuxc : Genode::Attached_mmio<0x10000>
{
	enum {
		PINCTRL_MMIO_BASE = 0x30330000,
		PINCTRL_MMIO_SIZE = 0x10000,
	};

	struct Mux : Mmio<32>
	{
		struct Reg : Register<0, 32>
		{
			struct Mode : Bitfield<0,3> {};
		};

		Mux(Byte_range_ptr const &range, Reg::access_t mux_mode)
		:
			Mmio<SIZE>(range)
		{
			write<Reg::Mode>(mux_mode);
		}
	};

	struct Misc : Mmio<32>
	{
		struct Reg : Register<0, 32> { };

		Misc(Byte_range_ptr const &range, Reg::access_t val)
		:
			Mmio<SIZE>(range)
		{
			write<Reg>(val);
		}
	};

	Iomuxc(Env &env)
	:
		Attached_mmio<SIZE>(env, { (char*)PINCTRL_MMIO_BASE, SIZE })
	{
		unsigned count = sizeof(pinctrl_setting) / (MAX*sizeof(uint32_t));
		for (unsigned i = 0; i < count; i++) {
			Mux mux(range_at(pinctrl_setting[i][MUX_REG]),
			        pinctrl_setting[i][MUX_MODE]);
			Misc conf(range_at(pinctrl_setting[i][CONF_REG]),
			        pinctrl_setting[i][CONF_VAL]);

			/* set input register only if it is set != 0 */
			if (pinctrl_setting[i][INPUT_REG])
				Misc input(range_at(pinctrl_setting[i][INPUT_REG]),
				           pinctrl_setting[i][INPUT_VAL]);
		}
	}
};

#endif /* __PLATFORM__IMX__IOMUXC_H_ */
