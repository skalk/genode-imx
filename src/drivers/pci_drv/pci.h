
#include <base/log.h>
#include <util/reconstructible.h>
#include <util/mmio.h>

namespace Pci {
	struct Config;
	struct Config_type0;
	struct Config_type1;
};

struct Pci::Config : Genode::Mmio
{
	struct Vendor : Register<0x0, 16> {};
	struct Device : Register<0x2, 16> {};

	struct Command : Register<0x4, 16>
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

	struct Status : Register<0x6, 16>
	{
		struct Interrupt    : Bitfield<3,1> {};
		struct Capabilities : Bitfield<4,1> {};
	};

	struct Class_code_rev_id : Register<0x8, 32>
	{
		struct Class_code : Bitfield<8, 24> {};
	};

	struct Iface_class_code : Register<0x9, 8> {};
	struct Sub_class_code   : Register<0xa, 8> {};
	struct Base_class_code  : Register<0xb, 8> {};

	struct Header_type : Register<0xe, 8> {};

	struct Base_address_0 : Register<0x10, 32> {};
	struct Base_address_1 : Register<0x14, 32> {};

	struct Capability_pointer : Register<0x34, 8> {};

	struct Irq_line : Register<0x3c, 8> {};
	struct Irq_pin  : Register<0x3d, 8> {};


	/**********************
	 ** PCI Capabilities **
	 **********************/

	struct Pci_capability : Genode::Mmio
	{
		struct Id : Register<0,8>
		{
			enum {
				POWER_MANAGEMENT = 0x1,
				MSI              = 0x5,
				PCI_E            = 0x10,
				MSI_X            = 0x11,
			};
		};

		struct Pointer : Register<1,8> {};

		using Genode::Mmio::Mmio;
	};


	struct Power_management_capability : Pci_capability
	{
		struct Capabilities   : Register<0x2, 16> {};
		struct Control_status : Register<0x4, 16>
		{
			struct Pme_status : Bitfield<15,1> {};
		};
		struct Data           : Register<0x7,  8> {};

		using Pci_capability::Pci_capability;
	};


	struct Msi_capability : Pci_capability
	{
		struct Control : Register<0x2, 16>
		{
			struct Enable                : Bitfield<0,1> {};
			struct Multi_message_capable : Bitfield<1,3> {};
			struct Multi_message_enable  : Bitfield<4,3> {};
			struct Large_address_capable : Bitfield<7,1> {};
		};

		struct Address_32 : Register<0x4, 32> {};
		struct Data_32    : Register<0x8,  8> {};

		struct Address_64_lower : Register<0x4, 32> {};
		struct Address_64_upper : Register<0x8, 32> {};
		struct Data_64          : Register<0xc,  8> {};

		using Pci_capability::Pci_capability;
	};


	struct Msi_x_capability : Pci_capability
	{
		struct Control : Register<0x2, 16>
		{
			struct Size          : Bitfield<0,  11> {};
			struct Function_mask : Bitfield<14, 1> {};
			struct Enable        : Bitfield<15, 1> {};
		};

		struct Table_offset             : Register<0x4, 32> {};
		struct Pending_bit_array_offset : Register<0x8, 32> {};

		using Pci_capability::Pci_capability;
	};


	struct Pci_express_capability : Pci_capability
	{
		struct Capabilities        : Register<0x2,  16> {};
		struct Device_capabilities : Register<0x4,  32> {};
		struct Device_control      : Register<0x8,  16> {};

		struct Device_status       : Register<0xa,  16>
		{
			struct Correctable_error    : Bitfield<0, 1> {};
			struct Non_fatal_error      : Bitfield<1, 1> {};
			struct Fatal_error          : Bitfield<2, 1> {};
			struct Unsupported_request  : Bitfield<3, 1> {};
			struct Aux_power            : Bitfield<4, 1> {};
			struct Transactions_pending : Bitfield<5, 1> {};
		};

		struct Link_capabilities : Register<0xc,  32>
		{
			struct Max_link_speed : Bitfield<0, 4> {};
		};

		struct Link_control : Register<0x10, 16>
		{
			struct Lbm_irq_enable : Bitfield<10,1> {};
		};

		struct Link_status : Register<0x12, 16>
		{
			struct Lbm_status : Bitfield<10,1> {};
		};

		struct Slot_capabilities   : Register<0x14, 32> {};
		struct Slot_control        : Register<0x18, 16> {};
		struct Slot_status         : Register<0x1a, 16> {};

		struct Root_control : Register<0x1c, 16>
		{
			struct Pme_irq_enable : Bitfield<3,1> {};
		};

		struct Root_status : Register<0x20, 32>
		{
			struct Pme : Bitfield<16,1> {};
		};

		struct Device_capabilities_2 : Register<0x24, 32> {};
		struct Device_control_2      : Register<0x28, 16> {};
		struct Device_status_2       : Register<0x2a, 16> {};
		struct Link_capabilities_2   : Register<0x2c, 32> {};

		struct Link_control_2 : Register<0x30, 16>
		{
			struct Link_speed : Bitfield<0, 4> {};
		};

		struct Link_status_2         : Register<0x32, 16> {};
		struct Slot_capabilities_2   : Register<0x34, 32> {};
		struct Slot_control_2        : Register<0x38, 16> {};
		struct Slot_status_2         : Register<0x3a, 16> {};

		using Pci_capability::Pci_capability;

		void power_management_event_enable()
		{
			write<Root_status::Pme>(1);
			write<Root_control::Pme_irq_enable>(1);
		};

		void clear_dev_errors()
		{
			Device_status::access_t v = read<Device_status>();
			Device_status::Correctable_error::set(v,1);
			Device_status::Non_fatal_error::set(v,1);
			Device_status::Fatal_error::set(v,1);
			Device_status::Unsupported_request::set(v,1);
			Device_status::Aux_power::set(v,1);
			write<Device_status>(v);
		}

		void link_bandwidth_management_enable()
		{
			write<Link_status::Lbm_status>(1);
			write<Link_control::Lbm_irq_enable>(1);
		}
	};


	/*********************************
	 ** PCI-E extended capabilities **
	 *********************************/

	enum { PCI_E_EXTENDED_CAPS_OFFSET = 0x100U };

	struct Pci_express_extended_capability : Genode::Mmio
	{
		struct Id : Register<0,16>
		{
			enum {
				INVALID                  = 0x0,
				ADVANCED_ERROR_REPORTING = 0x1,
				VIRTUAL_CHANNEL          = 0x2,
				DEVICE_SERIAL_NUMBER     = 0x3,
				POWER_BUDGETING          = 0x4,
			};
		};

		struct Next_and_version : Register<16, 8>
		{
			struct Offset : Bitfield<4, 12> {};
		};

		using Genode::Mmio::Mmio;
	};


	struct Advanced_error_reporting_capability : Pci_express_extended_capability
	{
		struct Uncorrectable_error_status : Register<0x4,  32> {};
		struct Correctable_error_status   : Register<0x10, 32> {};

		struct Root_error_command : Register<0x2c, 32>
		{
			struct Correctable_error_enable : Bitfield<0,1> {};
			struct Non_fatal_error_enable   : Bitfield<1,1> {};
			struct Fatal_error_enable       : Bitfield<2,1> {};
		};

		struct Root_error_status : Register<0x30, 32> {};

		using Pci_express_extended_capability::Pci_express_extended_capability;

		void enable()
		{
			Root_error_command::access_t v = 0;
			Root_error_command::Correctable_error_enable::set(v,1);
			Root_error_command::Non_fatal_error_enable::set(v,1);
			Root_error_command::Fatal_error_enable::set(v,1);
			write<Root_error_command>(v);
		};

		void clear()
		{
			write<Root_error_status>(read<Root_error_status>());
			write<Correctable_error_status>(read<Correctable_error_status>());
			write<Uncorrectable_error_status>(read<Uncorrectable_error_status>());
		};
	};

	Genode::Constructible<Power_management_capability>         power_cap   {};
	Genode::Constructible<Msi_capability>                      msi_cap     {};
	Genode::Constructible<Msi_x_capability>                    msi_x_cap   {};
	Genode::Constructible<Pci_express_capability>              pci_e_cap   {};
	Genode::Constructible<Advanced_error_reporting_capability> adv_err_cap {};

	void clear_errors() {
		if (adv_err_cap.constructed()) adv_err_cap->clear(); }

	void scan()
	{
		using namespace Genode;

		if (!read<Status::Capabilities>())
			return;

		uint16_t off = read<Capability_pointer>();
		while (off) {
			Pci_capability cap(base() + off);
			switch(cap.read<Pci_capability::Id>()) {
			case Pci_capability::Id::POWER_MANAGEMENT:
				power_cap.construct(base()+off); break;
			case Pci_capability::Id::MSI:
				msi_cap.construct(base()+off); break;
			case Pci_capability::Id::MSI_X:
				msi_x_cap.construct(base()+off); break;
			case Pci_capability::Id::PCI_E:
				pci_e_cap.construct(base()+off); break;
			default:
				warning("Found unhandled capability ",
				        cap.read<Pci_capability::Id>(),
				        " at offset ", Hex(base()+off));
			}
			off = cap.read<Pci_capability::Pointer>();
		}

		if (!pci_e_cap.constructed())
			return;

		off = PCI_E_EXTENDED_CAPS_OFFSET;
		while (off) {
			Pci_express_extended_capability cap(base() + off);
			switch (cap.read<Pci_express_extended_capability::Id>()) {
			case Pci_express_extended_capability::Id::INVALID:
				return;
			case Pci_express_extended_capability::Id::ADVANCED_ERROR_REPORTING:
				adv_err_cap.construct(base() + off); break;
			default:
				warning("Found unhandled extended capability ",
				        cap.read<Pci_express_extended_capability::Id>(),
				        " at offset ", Hex(base()+off));
			}
			off = cap.read<Pci_express_extended_capability::Next_and_version::Offset>();
		}
	}

	using Genode::Mmio::Mmio;
};


struct Pci::Config_type0 : Pci::Config
{
	struct Base_address_2 : Register<0x18, 32> {};
	struct Base_address_3 : Register<0x1c, 32> {};
	struct Base_address_4 : Register<0x20, 32> {};
	struct Base_address_5 : Register<0x24, 32> {};

	struct Expansion_rom_base_addr : Register<0x30, 32> {};

	using Pci::Config::Config;
};


struct Pci::Config_type1 : Pci::Config
{
	struct Sec_lat_timer_bus : Register<0x18, 32>
	{
		struct Primary_bus   : Bitfield<0,  8> {};
		struct Secondary_bus : Bitfield<8,  8> {};
		struct Sub_bus       : Bitfield<16, 8> {};
	};

	struct Io_base_limit : Register<0x1c, 16> {};

	struct Memory_base_limit : Register<0x20, 32> {};

	struct Prefetchable_memory_base : Register<0x24, 32> {};
	struct Prefetchable_memory_base_upper : Register<0x28, 32> {};
	struct Prefetchable_memory_limit_upper : Register<0x2c, 32> {};

	struct Io_base_limit_upper : Register<0x30, 32> {};

	struct Expansion_rom_base_addr : Register<0x38, 32> {};

	struct Bridge_control : Register<0x3e, 16>
	{
		struct Serror : Bitfield<1, 1> {};
	};

	using Pci::Config::Config;
};
