TARGET   := imx_usdhc_drv
REQUIRES := arm_v8a
LIBS     := base
INC_DIR  := $(PRG_DIR)

LX_CONTRIB_DIR  := $(call select_from_ports,iot_gateway_linux)/linux

#
# lx_mmc
#

SRC_CC += main.cc
SRC_CC += time.cc
SRC_C  += dummies.c
SRC_C  += generated_dummies.c
SRC_C  += block.c
SRC_C  += lx_emul.c
SRC_C  += lx_emul/shadow/kernel/softirq.c
SRC_C  += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

SRC_CC += genode_c_api/block.cc
vpath genode_c_api/block.cc $(subst /genode_c_api,,$(call select_from_repositories,src/lib/genode_c_api))

#
# Lx_emul + Lx_kit
#

SRC_CC  += lx_emul/alloc.cc
SRC_CC  += lx_emul/clock.cc
SRC_CC  += lx_emul/debug.cc
SRC_CC  += lx_emul/init.cc
SRC_CC  += lx_emul/io_mem.cc
SRC_CC  += lx_emul/irq.cc
SRC_CC  += lx_emul/log.cc
SRC_CC  += lx_emul/page_virt.cc
SRC_CC  += lx_emul/task.cc
SRC_CC  += lx_emul/time.cc

SRC_C   += lx_emul/clocksource.c
SRC_C   += lx_emul/common_dummies.c
SRC_C   += lx_emul/irqchip.c
SRC_C   += lx_emul/start.c
SRC_C   += lx_emul/shadow/arch/arm64/kernel/smp.c
SRC_C   += lx_emul/shadow/arch/arm64/mm/ioremap.c
SRC_C   += lx_emul/shadow/drivers/base/power/common.c
SRC_C   += lx_emul/shadow/drivers/base/power/main.c
SRC_C   += lx_emul/shadow/drivers/base/power/runtime.c
SRC_C   += lx_emul/shadow/drivers/clk/clk.c
SRC_C   += lx_emul/shadow/drivers/clk/clkdev.c
SRC_C   += lx_emul/shadow/fs/exec.c
SRC_C   += lx_emul/shadow/kernel/cpu.c
SRC_C   += lx_emul/shadow/kernel/dma/mapping.c
SRC_C   += lx_emul/shadow/kernel/exit.c
SRC_C   += lx_emul/shadow/kernel/fork.c
SRC_C   += lx_emul/shadow/kernel/irq/spurious.c
SRC_C   += lx_emul/shadow/kernel/locking/spinlock.c
SRC_C   += lx_emul/shadow/kernel/pid.c
SRC_C   += lx_emul/shadow/kernel/printk/printk.c
SRC_C   += lx_emul/shadow/kernel/rcu/srcutree.c
SRC_C   += lx_emul/shadow/kernel/rcu/tree.c
SRC_C   += lx_emul/shadow/kernel/sched/core.c
SRC_C   += lx_emul/shadow/kernel/smp.c
SRC_C   += lx_emul/shadow/kernel/stop_machine.c
SRC_C   += lx_emul/shadow/lib/devres.c
SRC_C   += lx_emul/shadow/lib/smp_processor_id.c
SRC_C   += lx_emul/shadow/mm/memblock.c
SRC_C   += lx_emul/shadow/mm/page_alloc.c
SRC_C   += lx_emul/shadow/mm/percpu.c
SRC_C   += lx_emul/shadow/mm/slab_common.c
SRC_C   += lx_emul/shadow/mm/slub.c
SRC_C   += lx_emul/virt_to_page.c

SRC_CC  += lx_kit/console.cc
SRC_CC  += lx_kit/device.cc
SRC_CC  += lx_kit/env.cc
SRC_CC  += lx_kit/init.cc
SRC_CC  += lx_kit/memory.cc
SRC_CC  += lx_kit/scheduler.cc
SRC_CC  += lx_kit/task.cc
SRC_CC  += lx_kit/timeout.cc
SRC_S   += lx_kit/spec/arm_64/setjmp.S

DDE_LINUX_DIR := $(subst /src/include/lx_kit,,$(call select_from_repositories,src/include/lx_kit))

INC_DIR += $(REP_DIR)/src/include/imx8mm
INC_DIR += $(REP_DIR)/src/include/imx8mm/lx_generated/include
INC_DIR += $(REP_DIR)/src/include/imx8mm/lx_generated/include/generated/uapi
INC_DIR += $(REP_DIR)/src/include/imx8mm/lx_generated/arch/arm64/include
INC_DIR += $(REP_DIR)/src/include/imx8mm/lx_generated/arch/arm64/include/generated
INC_DIR += $(REP_DIR)/src/include/imx8mm/lx_generated/arch/arm64/include/generated/uapi
INC_DIR += $(DDE_LINUX_DIR)/src/include
INC_DIR += $(DDE_LINUX_DIR)/src/include/spec/arm_64
INC_DIR += $(DDE_LINUX_DIR)/src/include/lx_emul/shadow

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx8mm
vpath % $(DDE_LINUX_DIR)/src/lib

#
# linux kernel definitions
#

INC_DIR += $(LX_CONTRIB_DIR)/include
INC_DIR += $(LX_CONTRIB_DIR)/include/uapi
INC_DIR += $(LX_CONTRIB_DIR)/arch/arm64/include
INC_DIR += $(LX_CONTRIB_DIR)/arch/arm64/include/generated
INC_DIR += $(LX_CONTRIB_DIR)/arch/arm64/include/uapi
INC_DIR += $(LX_CONTRIB_DIR)/scripts/dtc/libfdt
INC_DIR += $(LX_CONTRIB_DIR)/tools/include
INC_DIR += $(LX_CONTRIB_DIR)/tools/include/uapi

CC_C_OPT += -std=gnu89 -include $(LX_CONTRIB_DIR)/include/linux/kconfig.h
CC_C_OPT += -include $(LX_CONTRIB_DIR)/include/linux/compiler_types.h
CC_C_OPT += -D__KERNEL__ -DCONFIG_CC_HAS_K_CONSTRAINT=1 -DCONFIG_ARM64_PA_BITS=48
CC_C_OPT += -DKASAN_SHADOW_SCALE_SHIFT=3
CC_C_OPT += -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs
CC_C_OPT += -Werror=implicit-function-declaration -Werror=implicit-int
CC_C_OPT += -Wno-format-security -Wno-psabi
CC_C_OPT += -Wno-frame-address -Wno-format-truncation -Wno-format-overflow
CC_C_OPT += -Wframe-larger-than=2048 -Wno-unused-but-set-variable -Wimplicit-fallthrough
CC_C_OPT += -Wno-unused-const-variable -Wdeclaration-after-statement -Wvla
CC_C_OPT += -Wno-pointer-sign -Wno-stringop-truncation -Wno-array-bounds -Wno-stringop-overflow
CC_C_OPT += -Wno-restrict -Wno-maybe-uninitialized -Werror=date-time
CC_C_OPT += -Werror=incompatible-pointer-types -Werror=designated-init
CC_C_OPT += -Wno-packed-not-aligned

INC_DIR += $(LX_BUILD_DIR)/lib

CC_OPT_drivers/base/regmap/regmap  += -I$(LX_CONTRIB_DIR)/drivers/base/regmap

LX_SRC = $(shell grep ".*\.c" $(PRG_DIR)/source.list)
SRC_S  += $(shell grep ".*\.S" $(PRG_DIR)/source.list)
SRC_C  += $(LX_SRC)
SRC_S  += $(LX_ASM:$(LX_CONTRIB_DIR)/%=%)

#
# Create symbol alias for jiffies, sharing the value of jiffies_64
#
LD_OPT += --defsym=jiffies=jiffies_64

vpath %.c $(LX_CONTRIB_DIR)
vpath %.S $(LX_CONTRIB_DIR)

# Define per-compilation-unit CC_OPT defines needed by MODULE* macros in Linux
define CC_OPT_LX_RULES =
CC_OPT_$(1) += -DKBUILD_MODFILE='"$(1)"' -DKBUILD_BASENAME='"$(notdir $(1))"' -DKBUILD_MODNAME='"$(notdir $(1))"'
endef

$(foreach file,$(LX_SRC),$(eval $(call CC_OPT_LX_RULES,$(file:%.c=%))))

#
# Generate driver-specific device-tree binary data
#
# The rules below use the tool/dts/extract tool to generate a device tree
# containing the driver parameters for a given board.
#
# The resulting dtb file is named <driver>-<board>.dtb
#

BOARDS := imx8mmq_compulab_iot_gateway-usdhc2 \
          imx8mmq_compulab_iot_gateway-usdhc3

DTS_PATH(imx8mmq_compulab_iot_gateway-usdhc2)    := arch/arm64/boot/dts/compulab/sb-iotgimx8.dts
DTS_EXTRACT(imx8mmq_compulab_iot_gateway-usdhc2) := --select usdhc2

DTS_PATH(imx8mmq_compulab_iot_gateway-usdhc3)    := arch/arm64/boot/dts/compulab/sb-iotgimx8.dts
DTS_EXTRACT(imx8mmq_compulab_iot_gateway-usdhc3) := --select usdhc3

DTS_TOOL           := $(BASE_DIR)/../../tool/dts/extract
CUSTOM_TARGET_DEPS += $(addprefix $(INSTALL_DIR)/$(TARGET)-,$(addsuffix .dtb,$(BOARDS)))

$(INSTALL_DIR)/%.dtb: %.dtb
	$(VERBOSE)cp -f $< $@

%.dtb: %.dts
	$(VERBOSE)dtc -q -Idts $< > $@

# dependencies of driver's specific dts files from board's dts files
$(foreach B,$(BOARDS),$(eval $(TARGET)-$B.dts: $(LX_CONTRIB_DIR)/${DTS_PATH($B)}))
$(TARGET)-%.dts:
	$(VERBOSE)$(CROSS_DEV_PREFIX)cpp -I$(LX_CONTRIB_DIR)/include \
	          -x assembler-with-cpp -MMD -P $(LX_CONTRIB_DIR)/${DTS_PATH($*)} |\
	          sed -s 's/interrupt-parent = <\&gpc>;/interrupt-parent = <\&gic>;/' | \
	          $(DTS_TOOL) ${DTS_EXTRACT($*)} - > $@
