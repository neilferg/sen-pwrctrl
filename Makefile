# Variables affecting build:
#     CONFIG_TARGET        - pwrctrl_arm
#     CONFIG_DEBUG_BUILD   - =y => Debug build else Release
#     BUILD_DIR=<path>     - where to put compiled binaries

#---------------------------------------------------------
THIS_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
TOP_DIR  ?= $(abspath $(THIS_DIR))

# IN: CONFIG_TARGET, [CONFIG_DEBUG_BUILD]
CONFIG_TARGET ?= pwrctrl_arm
include $(TOP_DIR)/mk/tgt_vars.mk
# OUT: PRODUCT, TARGET, MODE, [CONFIG_HOST_BUILD], [CONFIG_DEBUG_BUILD]

BUILD_DIR ?= $(TOP_DIR)/Binaries


# PICO_SDK_PATH=/home/dev/pico/pico-sdk
# PICO_EXTRAS_PATH=/home/dev/pico/pico-extras
# PICO_PLAYGROUND_PATH=/home/dev/pico/pico-playground
# PICO_EXAMPLES_PATH=/home/dev/pico/pico-examples

PICO_SDK_PATH :=
export PICO_SDK_PATH

PICO_EXTRAS_PATH :=
export PICO_EXTRAS_PATH

PICO_PLAYGROUND_PATH :=
export PICO_PLAYGROUND_PATH

PICO_EXAMPLES_PATH :=
export PICO_EXAMPLES_PATH

#------------------------------------

OBJECT_DIR := $(BUILD_DIR)/$(MODE)
TARGET_BINARY := SenPwrCtrl.elf

CMAKE_OPTS :=
ifeq ($(MODE),Debug)
    CMAKE_OPTS += -DCMAKE_BUILD_TYPE=Debug
else
    CMAKE_OPTS += -DCMAKE_BUILD_TYPE=RelWithDebInfo
endif

.DEFAULT_GOAL := all
.PHONY: all build clean

build all:
	mkdir -p $(OBJECT_DIR); cd $(OBJECT_DIR); cmake $(CMAKE_OPTS) ../../src
	make -C $(OBJECT_DIR)

clean:
	rm -rf $(BUILD_DIR)
