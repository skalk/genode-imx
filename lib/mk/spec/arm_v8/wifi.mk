REQUIRES := arm_v8a

ORIGINAL_LIB_DIR := $(REP_DIR)/../pc/src/lib/wifi
TARGET_LIB_DIR   := $(REP_DIR)/src/lib/wifi

SHARED_LIB := yes

LD_OPT  += --version-script=$(ORIGINAL_LIB_DIR)/symbol.map

LIBS    += base jitterentropy imx_wifi_linux_generated imx_wifi_lx_emul
INC_DIR += $(TARGET_LIB_DIR)
INC_DIR += $(ORIGINAL_LIB_DIR)
SRC_CC  += wlan.cc
SRC_CC  += misc.cc
SRC_CC  += firmware.cc
SRC_CC  += socket_call.cc
SRC_CC  += lx_emul/random.cc
SRC_CC  += time.cc

SRC_C   += dummies.c
SRC_C   += lx_emul.c
SRC_C   += lx_user.c
SRC_C   += uplink.c
SRC_C   += lx_socket_call.c
SRC_C   += $(notdir $(wildcard $(REP_DIR)/src/lib/wifi/generated_dummies.c))
SRC_C   += lx_emul/shadow/lib/kobject_uevent.c

CC_C_OPT += -I$(LX_SRC_DIR)/drivers/net/wireless/intel/iwlwifi
CC_C_OPT += -Wno-address-of-packed-member
CC_C_OPT += -DCONFIG_RFKILL_INPUT

CC_OPT_lx_socket_call     += -DKBUILD_MODNAME='"lx_socket_call"'
CC_OPT_dummies            += -DKBUILD_MODNAME='"dummies"'
CC_OPT_generated_dummies  += -DKBUILD_MODNAME='"generated_dummies"'
CC_OPT_net/mac80211/trace += -I$(LX_SRC_DIR)/net/mac80211
CC_OPT_net/wireless/trace += -I$(LX_SRC_DIR)/net/wireless

vpath %.c  $(TARGET_LIB_DIR)
vpath %.cc $(TARGET_LIB_DIR)
vpath %.c  $(ORIGINAL_LIB_DIR)
vpath %.cc $(ORIGINAL_LIB_DIR)

vpath %.c $(REP_DIR)/../pc/src/lib/pc

$(LIB).lib.so: $(ORIGINAL_LIB_DIR)/symbol.map

#
# Genode C-API backends
#

SRC_CC  += genode_c_api/uplink.cc

vpath genode_c_api/uplink.cc $(subst /genode_c_api,,$(call select_from_repositories,src/lib/genode_c_api))
