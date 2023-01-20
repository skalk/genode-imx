TARGET  := ath9k_wifi_drv
SRC_CC  := main.cc wpa.cc
LIBS    := base wifi wifi_firmware
LIBS    += libc
LIBS    += wpa_supplicant
LIBS    += libcrypto libssl wpa_driver_nl80211

INC_DIR += $(REPOS_DIR)/../pc/src/drivers/wifi/pc

CC_CXX_WARN_STRICT :=

INC_DIR += $(REP_DIR)/../pc/src/drivers/wifi/pc

vpath %.cc $(REP_DIR)/../pc/src/drivers/wifi/pc
