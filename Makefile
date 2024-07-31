
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

MODE := Debug
BUILD_DIR := Binaries
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
