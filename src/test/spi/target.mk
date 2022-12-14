TARGET    = test-spi

GTEST_DIR := $(call select_from_ports,googletest)/src/lib/googletest/googletest

SRC_CC   := gtest_main.cc
SRC_CC   += spi_shiftregister.cc

vpath gtest_main.cc $(GTEST_DIR)/src

LIBS += base
LIBS += gtest
LIBS += libc
LIBS += gtest_component
LIBS += stdcxx
LIBS += vfs

CC_CXX_WARN_STRICT = -Wextra -Werror
