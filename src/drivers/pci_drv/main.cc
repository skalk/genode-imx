#include <base/component.h>
#include <base/log.h>
#include <gpio_session/connection.h>
#include <platform_session/device.h>
#include <timer_session/connection.h>
#include <util/xml_generator.h>

#include <pci.h>

using namespace Genode;


struct Pci_device : Platform::Device::Mmio
{
	Pci::Config_type0 cfg;

	Pci_device(Platform::Device            & device,
	           Platform::Device::Mmio::Index i)
	: Platform::Device::Mmio(device, i),
	  cfg(base()) { }

};


struct Pcie_controller : Platform::Device::Mmio
{
	enum Transaction_type {
		MEMORY_REQUEST        = 0,
		IO_REQUEST            = 2,
		CONFIG_TYPE_0_REQUEST = 4,
		CONFIG_TYPE_1_REQUEST = 5
	};

	struct Port_link_control : Register<0x710, 32>
	{
		struct Dll_link_enable : Bitfield<5,  1> {};
		struct Fast_link_mode  : Bitfield<7,  1> {};
		struct Link_capable    : Bitfield<16, 6> {};
	};

	struct Port_debug1 : Register<0x72c, 32>
	{
		struct Link_up          : Bitfield<4,  1> {};
		struct Link_in_training : Bitfield<29, 1> {};
	};

	struct Link_width_speed_control : Register<0x80c, 32>
	{
		struct Num_of_lanes        : Bitfield<8,  5> {};
		struct Direct_speed_change : Bitfield<17, 1> {};
	};

	struct Msi_control_address       : Register<0x820, 32> {};
	struct Msi_control_upper_address : Register<0x824, 32> {};
	struct Msi_control_enable        : Register<0x828, 32> {};
	struct Msi_control_mask          : Register<0x82c, 32> {};
	struct Msi_control_status        : Register<0x830, 32> {};

	struct Misc_control1 : Register<0x8bc, 32>
	{
		struct Dbi_ro_wr_enable : Bitfield<0, 1> {};
	};

	struct Atu : Genode::Mmio
	{
		struct Atu_region_control_1 : Register<0x0, 32>
		{
			struct Type     : Bitfield<0,  5> {};
			struct Tc       : Bitfield<5,  3> {};
			struct Td       : Bitfield<8,  1> {};
			struct Attr     : Bitfield<9,  2> {};
			struct At       : Bitfield<16, 2> {};
			struct Function : Bitfield<20, 3> {};
		};

		struct Atu_region_control_2 : Register<0x4, 32>
		{
			struct Shift_mode  : Bitfield<28, 1> {};
			struct Invert_mode : Bitfield<29, 1> {};
			struct Enable      : Bitfield<31, 1> {};
		};

		struct Atu_lower_base_addr   : Register<0x8,  32> {};
		struct Atu_upper_base_addr   : Register<0xc,  32> {};
		struct Atu_limit_addr        : Register<0x10, 32> {};
		struct Atu_lower_target_addr : Register<0x14, 32> {};
		struct Atu_upper_target_addr : Register<0x18, 32> {};

		Atu(addr_t const base) : Genode::Mmio(base) {}

		void configure_outbound(Transaction_type type,
		                        addr_t cpu_addr, size_t size,
		                        addr_t pci_addr)
		{
			typename Atu_region_control_1::access_t ctrl1 = 0;
			Atu_region_control_1::Type::set(ctrl1, type);
			write<Atu_region_control_1>(ctrl1);

			typename Atu_region_control_2::access_t ctrl2 = 0;
			Atu_region_control_2::Enable::set(ctrl2, 1);
			write<Atu_region_control_2>(ctrl2);

			write<Atu_lower_base_addr>(cpu_addr & 0xffffffff);
			write<Atu_upper_base_addr>(cpu_addr >> 32);
			write<Atu_limit_addr>((cpu_addr + size - 1) & 0xffffffff);
			write<Atu_lower_target_addr>(pci_addr & 0xffffffff);
			write<Atu_upper_target_addr>(pci_addr >> 32);
		}

		void disable_outbound()
		{
			Atu_region_control_2::access_t ctrl2 = 0;
			Atu_region_control_2::Enable::set(ctrl2, 1);
			write<Atu_region_control_2>(ctrl2);
		}

		bool up() { return read<Atu_region_control_2::Enable>(); }
	} atu[4] { { Platform::Device::Mmio::base() + 0x300000 },
	           { Platform::Device::Mmio::base() + 0x300200 },
	           { Platform::Device::Mmio::base() + 0x300400 },
	           { Platform::Device::Mmio::base() + 0x300600 } };

	Pci::Config_type1 cfg;

	struct Atu_is_not_ready  {};
	struct Link_is_not_ready {};

	Timer::Connection & timer;

	bool link_up()
	{
		return read<Port_debug1::Link_up>() &&
		       !read<Port_debug1::Link_in_training>();
	}

	bool wait_for_link()
	{
		for (unsigned i = 0; i < 10; i++) {
			if (link_up())
				return true;
			timer.msleep(100);
		}
		return false;
	}

	bool wait_for_atu()
	{
		for (unsigned i = 0; i < 10; i++) {
			if (atu[0].up())
				return true;
			timer.msleep(10);
		}
		return true;
	}

	Pcie_controller(Timer::Connection           & timer,
	                Platform::Device            & device,
	                Platform::Device::Mmio::Index i)
	: Mmio(device, i),
	  cfg(base()),
	  timer(timer)
	{
		using namespace Pci;

		cfg.scan();

		write<Misc_control1::Dbi_ro_wr_enable>(1);
		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_control_2::Link_speed>(2);
		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_capabilities::Max_link_speed>(2);
		write<Port_link_control::Fast_link_mode>(0);
		write<Port_link_control::Dll_link_enable>(1);
		write<Port_link_control::Link_capable>(1);
		write<Link_width_speed_control::Num_of_lanes>(1);

		cfg.write<Config::Base_address_0>(4);
		cfg.write<Config::Base_address_1>(0);
		cfg.write<Config::Irq_line>(0xff);
		cfg.write<Config::Irq_pin>(0x1);

		Config_type1::Sec_lat_timer_bus::access_t bus =
			read<Config_type1::Sec_lat_timer_bus>();
		Config_type1::Sec_lat_timer_bus::Primary_bus::set(bus, 0);
		Config_type1::Sec_lat_timer_bus::Secondary_bus::set(bus, 1);
		Config_type1::Sec_lat_timer_bus::Sub_bus::set(bus, 0xff);
		cfg.write<Config_type1::Sec_lat_timer_bus>(bus);

		Config::Command::access_t cmd = 0;
		Config::Command::Io_space_enable::set(cmd, 1);
		Config::Command::Memory_space_enable::set(cmd, 1);
		Config::Command::Bus_master_enable::set(cmd, 1);
		Config::Command::Serror_enable::set(cmd, 1);
		cfg.write<Config::Command>(cmd);

		/* disable all outbound windows */
		for (unsigned i = 0; i < 4; i++)
			atu[i].disable_outbound();

		atu[1].configure_outbound(MEMORY_REQUEST, 0x20000000, 0x7f00000, 0x20000000);
		atu[2].configure_outbound(IO_REQUEST, 0x27f80000, 0x10000, 0);

		cfg.write<Config::Base_address_0>(0);

		/* we're a PCI bridge */
		cfg.write<Config::Sub_class_code>(0x04);
		cfg.write<Config::Base_class_code>(0x06);
		write<Link_width_speed_control::Direct_speed_change>(1);
		write<Misc_control1::Dbi_ro_wr_enable>(0);

		/*
		 * Force Gen1 when starting the link. In case the link is
		 * started in Gen2 mode, there is a possibility the devices on the
		 * bus will not be detected at all.
		 */
		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_capabilities::Max_link_speed>(1);

		if (!wait_for_link())
			throw Link_is_not_ready();

		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_capabilities::Max_link_speed>(2);
		write<Link_width_speed_control::Direct_speed_change>(1);

		if (!wait_for_link())
			throw Link_is_not_ready();

		atu[0].configure_outbound(CONFIG_TYPE_0_REQUEST, 0x27f00000, 0x80000, 1<<24);
		if (!wait_for_atu())
			throw Atu_is_not_ready();

		cfg.write<Config_type1::Base_address_1>(0);
		cfg.write<Config_type1::Expansion_rom_base_addr>(0);
		cfg.write<Config_type1::Io_base_limit>(0);
		cfg.write<Config_type1::Prefetchable_memory_base>(0);
		Config_type1::Bridge_control::access_t br_ctl = 0;
		Config_type1::Bridge_control::Serror::set(br_ctl, 1);
		cfg.write<Config_type1::Bridge_control>(br_ctl);
		cfg.power_cap->write<Config::Power_management_capability::Control_status::Pme_status>(1);
		cfg.clear_errors();
	}
};


struct Main
{
	Env & env;

	/* Dummy wait for GPIO settings being settled */
	Reconstructible<Gpio::Connection> gpio { env, 255 };

	Platform::Connection platform   { env                  };
	Platform::Device     device     { platform             };
	Timer::Connection    timer      { env                  };
	Pcie_controller      controller { timer, device, { 0 } };
	Pci_device           pci_dev    { device, { 1 }        };

	Main(Env & env) : env(env)
	{
		using namespace Pci;

		gpio.destruct();

		pci_dev.cfg.scan();

		pci_dev.cfg.write<Config_type0::Command>(0);
		pci_dev.cfg.write<Config_type0::Base_address_0>(4);
		pci_dev.cfg.write<Config_type0::Base_address_1>(0);
		pci_dev.cfg.write<Config_type0::Base_address_2>(0);
		pci_dev.cfg.write<Config_type0::Base_address_3>(0);
		pci_dev.cfg.write<Config_type0::Base_address_4>(0);
		pci_dev.cfg.write<Config_type0::Base_address_5>(0);
		pci_dev.cfg.write<Config_type0::Expansion_rom_base_addr>(0);
		pci_dev.cfg.clear_errors();

		controller.cfg.write<Config::Base_address_0>(0x20000000);
		pci_dev.cfg.write<Config::Base_address_0>(0x20100004);
		controller.cfg.write<Config_type1::Io_base_limit_upper>(0xffff);
		controller.cfg.write<Config_type1::Io_base_limit>(0xf0);
		controller.cfg.write<Config_type1::Io_base_limit_upper>(0);
		controller.cfg.write<Config_type1::Memory_base_limit>(0x20102010);
		controller.cfg.write<Config_type1::Prefetchable_memory_limit_upper>(0);
		controller.cfg.write<Config_type1::Prefetchable_memory_base>(0xfff0);
		controller.cfg.write<Config_type1::Prefetchable_memory_base_upper>(0);
		controller.cfg.write<Config_type1::Prefetchable_memory_limit_upper>(0);
		controller.cfg.write<Config_type1::Irq_line>(0x59);

		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Root_control>(0);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Root_status>(0x10000);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Root_control>(0x8);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Link_status>(0x4000);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Link_control>(0x400);

		pci_dev.cfg.write<Config::Command>(0x2);
		pci_dev.cfg.write<Config::Command>(0x6);
		pci_dev.cfg.pci_e_cap->write<Config::Pci_express_capability::Slot_control>(0x201f);
	}
};


void Component::construct(Env & env) {
	static Main main(env); }
