# ------------------------------------------------
# IN:
CONFIG_TARGET      ?= pwrctrl_arm
CONFIG_DEBUG_BUILD ?=

# ------------------------------------------------
# OUT:
# PRODUCT, TARGET, MODE, CONFIG_HOST_BUILD, CONFIG_DEBUG_BUILD

PRODUCT = pwrctrl

TARGET         := $(CONFIG_TARGET)

# If CONFIG_DEBUG_BUILD has a value, then the user
# has forced a build MODE
ifeq ($(strip $(CONFIG_DEBUG_BUILD)),y)
    MODE = Debug
else ifeq ($(strip $(CONFIG_DEBUG_BUILD)),n)
    MODE = Release
else
    # Use the default for the TARGET as defined below
endif

ifeq ($(CONFIG_TARGET),pwrctrl_arm)
    MODE ?= Release
else
    $(error TARGET=$(TARGET) is not supported. Valid are: pwrctrl_arm)
endif

# Set CONFIG_DEBUG_BUILD if MODE=Debug
ifeq ($(strip $(MODE)),Debug)
    CONFIG_DEBUG_BUILD=y
endif

$(info TARGET=$(TARGET), MODE=$(MODE), CONFIG_HOST_BUILD=$(CONFIG_HOST_BUILD) CONFIG_DEBUG_BUILD=$(CONFIG_DEBUG_BUILD))
