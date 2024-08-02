cmake_minimum_required(VERSION 3.16)

include(../../pico-sdk/pico_sdk_init.cmake)

project(SenPwrCtrl)

pico_sdk_init()

add_executable(SenPwrCtrl
    main.cpp
    slave_mem_i2c.cpp
)

target_link_libraries(SenPwrCtrl
    pico_stdlib
    hardware_adc
    pico_i2c_slave
    hardware_i2c
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(SenPwrCtrl)

# Enable USB serial
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # use picoprobe's uart
    pico_enable_stdio_usb(SenPwrCtrl 0)
    pico_enable_stdio_uart(SenPwrCtrl 1)
else()
    pico_enable_stdio_usb(SenPwrCtrl 1)
    pico_enable_stdio_uart(SenPwrCtrl 0)
endif()

FIND_PROGRAM(OBJCOPY arm-none-eabi-objcopy)

ADD_CUSTOM_COMMAND(TARGET SenPwrCtrl POST_BUILD
    COMMAND ${OBJCOPY} --only-keep-debug $<TARGET_FILE:SenPwrCtrl> ${CMAKE_BINARY_DIR}/SenPwrCtrl.debug
    COMMAND ${OBJCOPY} --strip-debug $<TARGET_FILE:SenPwrCtrl>
    COMMAND ${OBJCOPY} --add-gnu-debuglink=SenPwrCtrl.debug $<TARGET_FILE:SenPwrCtrl>
)
