LIBS += imx_wifi_linux_generated

LX_SRC_DIR := $(call select_from_ports,linux)/src/linux
ifeq ($(wildcard $(LX_SRC_DIR)),)
LX_SRC_DIR := $(call select_from_repositories,src/linux)
endif

LX_GEN_DIR := $(LIB_CACHE_DIR)/imx_wifi_linux_generated

include $(call select_from_repositories,lib/import/import-lx_emul_common.inc)

SRC_CC  += lx_emul/clock.cc
SRC_CC  += lx_emul/io_mem.cc
SRC_CC  += lx_emul/io_port.cc
SRC_CC  += lx_emul/irq.cc
SRC_CC  += lx_emul/random.cc
SRC_C   += lx_emul/shadow/arch/arm64/kernel/smp.c
SRC_C   += lx_emul/shadow/kernel/dma/mapping.c
SRC_C   += lx_emul/shadow/kernel/irq/spurious.c
SRC_C   += lx_emul/shadow/lib/devres.c
SRC_C   += lx_emul/shadow/lib/smp_processor_id.c
SRC_C   += lx_emul/shadow/mm/memblock.c
SRC_C   += lx_emul/shadow/mm/page_alloc.c
SRC_C   += lx_emul/shadow/drivers/pci/host-bridge.c
SRC_C   += lx_emul/shadow/drivers/pci/pci.c
SRC_C   += lx_emul/shadow/drivers/pci/pci-sysfs.c
SRC_C   += lx_emul/shadow/drivers/pci/search.c
SRC_C   += lx_emul/shadow/drivers/pci/setup-irq.c
SRC_C   += lx_emul/shadow/drivers/pci/setup-res.c
SRC_CC  += lx_emul/pci.cc
SRC_CC  += lx_emul/pci_bus.c
SRC_CC  += lx_kit/device.cc
SRC_CC  += lx_kit/memory_dma.cc

SRC_C   += lx_emul/shadow/fs/sysfs/dir.c
SRC_C   += lx_emul/shadow/fs/sysfs/file.c
SRC_C   += lx_emul/shadow/fs/sysfs/group.c
SRC_C   += lx_emul/shadow/fs/sysfs/symlink.c

#
# Replacing implementations that could be merged into DDE Linux.
#
SRC_C   += lx_emul/mapping.c
SRC_C   += lx_emul/page_alloc.c
SRC_C   += lx_emul/sched_core.c
SRC_C   += lx_emul/slab_common.c
SRC_C   += lx_emul/vmalloc.c
SRC_C   += lx_emul/delay.c

SRC_C   += lx_emul/shadow/fs/libfs.c
SRC_C   += lx_emul/shadow/lib/logic_iomem.c

SRC_C   += lx_emul/shadow/drivers/char/random.c
SRC_C   += lx_emul/shadow/mm/dmapool.c
