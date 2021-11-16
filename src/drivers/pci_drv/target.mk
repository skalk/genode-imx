TARGET   = imx8mq_pci_drv
REQUIRES = arm_v8a
LIBS     = base
SRC_CC   = main.cc
INC_DIR  = $(PRG_DIR) $(BASE_DIR)/../os/src/drivers/platform/spec/arm

vpath %.cc $(PRG_DIR)
vpath %.cc $(BASE_DIR)/../os/src/drivers/platform/spec/arm
