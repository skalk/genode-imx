#include <base/component.h>
#include <base/log.h>
#include <platform_session/device.h>
#include <gpio_session/connection.h>
#include <timer_session/connection.h>

using namespace Genode;

struct Pcie_config_space : Platform::Device::Mmio
{
	struct Id : Register<0x0, 32>
	{
		struct Vendor : Bitfield<0,  16> {};
		struct Device : Bitfield<16, 16> {};
	};

	struct Class_code_rev_id : Register<0x8, 32> {};

	using Platform::Device::Mmio::Mmio;
};


struct Pcie_controller : Platform::Device::Mmio
{
	struct Status_command : Register<0x4, 32>
	{
		struct Io_space_enable         : Bitfield<0,  1> {};
		struct Memory_space_enable     : Bitfield<1,  1> {};
		struct Bus_master_enable       : Bitfield<2,  1> {};
		struct Special_cycle_enable    : Bitfield<3,  1> {};
		struct Memory_write_invalidate : Bitfield<4,  1> {};
		struct Vga_palette_snoop       : Bitfield<5,  1> {};
		struct Parity_error_response   : Bitfield<6,  1> {};
		struct Idsel                   : Bitfield<7,  1> {};
		struct Serror_enable           : Bitfield<8,  1> {};
		struct Interrupt_enable        : Bitfield<10, 1> {};
	};

	struct Class_code_rev_id : Register<0x8, 32>
	{
		struct Revision   : Bitfield<0,  8> {};
		struct Prg_iface  : Bitfield<8,  8> {};
		struct Sub_class  : Bitfield<16, 8> {};
		struct Base_class : Bitfield<24, 8> {};
	};

	struct Base_address_0 : Register<0x10, 32> {};
	struct Base_address_1 : Register<0x14, 32> {};

	struct Sec_lat_timer_bus : Register<0x18, 32>
	{
		struct Primary_bus   : Bitfield<0,  8> {};
		struct Secondary_bus : Bitfield<8,  8> {};
		struct Sub_bus       : Bitfield<16, 8> {};
	};

	struct Bridge_ctrl_irq_pin_line : Register<0x3c, 32>
	{
		struct Irq_pin : Bitfield<8, 8> {};
	};

	struct Link_capabilities : Register<0x7c, 32>
	{
		struct Max_link_speed : Bitfield<0, 4> {};
	};

	struct Link_control2_status2 : Register<0xa0, 32>
	{
		struct Link_speed : Bitfield<0, 4> {};
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

	struct Misc_control1 : Register<0x8bc, 32>
	{
		struct Dbi_ro_wr_enable : Bitfield<0, 1> {};
	};

	template <unsigned IDX>
	struct Atu_region_control_1 : Register<0x300000 + IDX*0x200, 32>
	{
		struct Type     : Register<0x300000 + IDX*0x200, 32>::template Bitfield<0,  5> {};
		struct Tc       : Register<0x300000 + IDX*0x200, 32>::template Bitfield<5,  3> {};
		struct Td       : Register<0x300000 + IDX*0x200, 32>::template Bitfield<8,  1> {};
		struct Attr     : Register<0x300000 + IDX*0x200, 32>::template Bitfield<9,  2> {};
		struct At       : Register<0x300000 + IDX*0x200, 32>::template Bitfield<16, 2> {};
		struct Function : Register<0x300000 + IDX*0x200, 32>::template Bitfield<20, 3> {};
	};

	template <unsigned IDX>
	struct Atu_region_control_2 : Register<0x300004 + IDX*0x200, 32>
	{
		struct Shift_mode  : Register<0x300004 + IDX*0x200, 32>::template Bitfield<28, 1> {};
		struct Invert_mode : Register<0x300004 + IDX*0x200, 32>::template Bitfield<29, 1> {};
		struct Enable      : Register<0x300004 + IDX*0x200, 32>::template Bitfield<31, 1> {};
	};

	template <unsigned IDX> struct Atu_lower_base_addr   : Register<0x300008 + IDX*0x200, 32> {};
	template <unsigned IDX> struct Atu_upper_base_addr   : Register<0x30000c + IDX*0x200, 32> {};
	template <unsigned IDX> struct Atu_limit_addr        : Register<0x300010 + IDX*0x200, 32> {};
	template <unsigned IDX> struct Atu_lower_target_addr : Register<0x300014 + IDX*0x200, 32> {};
	template <unsigned IDX> struct Atu_upper_target_addr : Register<0x300018 + IDX*0x200, 32> {};

	enum Transaction_type {
		MEMORY_REQUEST        = 0,
		IO_REQUEST            = 2,
		CONFIG_TYPE_0_REQUEST = 4,
		CONFIG_TYPE_1_REQUEST = 5
	};

	using Platform::Device::Mmio::Mmio;

	template <typename T>
	void writeb(typename T::access_t word)
	{
		//typedef typename T::Compound_reg Register;
		write<T>(word);
		//log("dw_pcie_write: ", Hex(Register::OFFSET), " ", read<Register>());
	}

	template <typename T>
	void writer(typename T::access_t word)
	{
		write<T>(word);
		//log("dw_pcie_write: ", Hex(T::OFFSET), " ", read<T>());
	}

	template <unsigned IDX>
	void configure_outbound_atu(Transaction_type type,
	                            addr_t cpu_addr, size_t size,
	                            addr_t pci_addr)
	{
		typename Atu_region_control_1<IDX>::access_t ctrl1 = 0;
		Atu_region_control_1<IDX>::Type::set(ctrl1, type);
		writer<Atu_region_control_1<IDX>>(ctrl1);

		typename Atu_region_control_2<IDX>::access_t ctrl2 = 0;
		Atu_region_control_2<IDX>::Enable::set(ctrl2, 1);
		writer<Atu_region_control_2<IDX>>(ctrl2);

		writer<Atu_lower_base_addr<IDX>>(cpu_addr & 0xffffffff);
		writer<Atu_upper_base_addr<IDX>>(cpu_addr >> 32);
		writer<Atu_limit_addr<IDX>>((cpu_addr + size - 1) & 0xffffffff);
		writer<Atu_lower_target_addr<IDX>>(pci_addr & 0xffffffff);
		writer<Atu_upper_target_addr<IDX>>(pci_addr >> 32);
	}

	void init()
	{
		writeb<Misc_control1::Dbi_ro_wr_enable>(1);
		writeb<Link_control2_status2::Link_speed>(2);
		writeb<Link_capabilities::Max_link_speed>(2);
		writeb<Port_link_control::Fast_link_mode>(0);
		writeb<Port_link_control::Dll_link_enable>(1);
		writeb<Port_link_control::Link_capable>(1);
		writeb<Link_width_speed_control::Num_of_lanes>(1);
		writer<Base_address_0>(4);
		writer<Base_address_1>(0);
		writeb<Bridge_ctrl_irq_pin_line::Irq_pin>(1);

		Sec_lat_timer_bus::access_t bus = read<Sec_lat_timer_bus>();
		Sec_lat_timer_bus::Primary_bus::set(bus, 0);
		Sec_lat_timer_bus::Secondary_bus::set(bus, 1);
		Sec_lat_timer_bus::Sub_bus::set(bus, 0xff);
		writer<Sec_lat_timer_bus>(bus);

		Status_command::access_t status = read<Status_command>();
		Status_command::Io_space_enable::set(status, 1);
		Status_command::Memory_space_enable::set(status, 1);
		Status_command::Bus_master_enable::set(status, 1);
		Status_command::Special_cycle_enable::set(status, 0);
		Status_command::Memory_write_invalidate::set(status, 0);
		Status_command::Vga_palette_snoop::set(status, 0);
		Status_command::Parity_error_response::set(status, 0);
		Status_command::Idsel::set(status, 0);
		Status_command::Serror_enable::set(status, 1);
		Status_command::Interrupt_enable::set(status, 0);
		writer<Status_command>(status);

		/* disable all outbound windows */
		typename Atu_region_control_2<0>::access_t ctrl2 = 0;
		Atu_region_control_2<0>::Enable::set(ctrl2, 1);
		writer<Atu_region_control_2<0>>(ctrl2);
		writer<Atu_region_control_2<1>>(ctrl2);
		writer<Atu_region_control_2<2>>(ctrl2);
		writer<Atu_region_control_2<3>>(ctrl2);

		configure_outbound_atu<1>(MEMORY_REQUEST,
		                       0x18000000, 0x7f00000, 0x18000000);
		configure_outbound_atu<2>(IO_REQUEST,
		                       0x1ff80000, 0x10000,   0);

		writer<Base_address_0>(0);

		/* we're a PCI bridge */
		writeb<Class_code_rev_id::Sub_class>(0x04);
		writeb<Class_code_rev_id::Base_class>(0x06);
		writeb<Link_width_speed_control::Direct_speed_change>(1);
		writeb<Misc_control1::Dbi_ro_wr_enable>(0);
	}

	bool link_up()
	{
		return read<Port_debug1::Link_up>() &&
		       !read<Port_debug1::Link_in_training>();
	}

	bool atu_up()
	{
		return read<Atu_region_control_2<0>::Enable>();
	}
};


struct Main
{
	using Reset_pin = Constructible<Platform::Device>;

	Env                & env;
	Platform::Connection platform   { env           };
	Platform::Device     device     { platform      };
	Pcie_controller      controller { device, { 0 } };
	Pcie_config_space    cfg_space  { device, { 1 } };
	Timer::Connection    timer      { env           };
	Gpio::Connection     gpio       { env, 7       };
	Reset_pin            phy_reset  {};
	Reset_pin            core_reset {};

	struct Atu_is_not_ready  {};
	struct Link_is_not_ready {};

	bool wait_for_link()
	{
		for (unsigned i = 0; i < 10; i++) {
			if (controller.link_up())
				return true;
			timer.msleep(100);
		}
		return false;
	}

	bool wait_for_atu()
	{
		for (unsigned i = 0; i < 10; i++) {
			if (controller.atu_up())
				return true;
			timer.msleep(10);
		}
		return true;
	}

	Main(Env & env) : env(env)
	{
		gpio.direction(Gpio::Session::OUT);
		gpio.write(false);
		timer.msleep(100);
		gpio.write(true);

		timer.msleep(100);
		phy_reset.construct(platform, Platform::Device::Type({"reset-pin,phy"}));

		controller.init();

		/*
		 * Force Gen1 when starting the link. In case the link is
		 * started in Gen2 mode, there is a possibility the devices on the
		 * bus will not be detected at all.
		 */
		controller.write<Pcie_controller::Link_capabilities::Max_link_speed>(1);

		core_reset.construct(platform, Platform::Device::Type({"reset-pin,core"}));

		if (!wait_for_link())
			throw Link_is_not_ready();

		controller.write<Pcie_controller::Link_capabilities::Max_link_speed>(2);
		controller.write<Pcie_controller::Link_width_speed_control::Direct_speed_change>(1);

		if (!wait_for_link())
			throw Link_is_not_ready();

		controller.configure_outbound_atu<0>(Pcie_controller::CONFIG_TYPE_0_REQUEST,
		                                  0x1ff00000, 0x80000, 1<<24);
		if (!wait_for_atu())
			throw Atu_is_not_ready();

		log("Ready to probe!");
		log(Hex(cfg_space.read<Pcie_config_space::Id>()));
		log(Hex(cfg_space.read<Pcie_config_space::Class_code_rev_id>()));
	}
};


void Component::construct(Env & env) {
	static Main main(env); }
