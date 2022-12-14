/*
 *  \brief  VFS plugin interface implementation
 *  \author Alice Domage
 *  \date   2022-06-28
 */

/* Genode includes */
#include <vfs/file_system_factory.h>
#include <vfs/single_file_system.h>

/* Local includes */
#include "spi_driver.h"
#include "spi_service.h"


/**************************
 ** VFS plugin interface **
 **************************/


extern "C" Vfs::File_system_factory *vfs_file_system_factory(void)
{
	struct Factory : Vfs::File_system_factory
	{
		Vfs::File_system *create(Vfs::Env &vfs_env,
		                         Genode::Xml_node node) override
		{
			try {
				auto *vfs = new (vfs_env.alloc()) Vfs_spi::Spi_file_system(vfs_env, node);
				return reinterpret_cast<Vfs::File_system*>(vfs);
			} catch (...) {
				Genode::error("could not create 'Spi vfs'");
			}
			return nullptr;
		}
	};
	static Factory factory;
	return &factory;
}
