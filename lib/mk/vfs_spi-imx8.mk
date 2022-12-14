SRC_CC = spi_gpio_device.cc spi_vfs.cc imx/imx8_ecspi.cc

INC_DIR += $(REP_DIR)/src/lib/vfs/spi

vpath % $(REP_DIR)/src/lib/vfs/spi

SHARED_LIB := yes
