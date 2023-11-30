cmake_minimum_required(VERSION 3.13)

add_executable(audit_tool)

target_sources(audit_tool PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/lib/msc_disk.c
        ${CMAKE_CURRENT_LIST_DIR}/lib/blackwhitelist/blackwhitelist.c
        )

#  Make sure TinyUSB can find tusb_config.h
target_include_directories(audit_tool PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/lib)

add_subdirectory(lib/FatFs_SPI build)

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(audit_tool PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board FatFs_SPI)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

pico_add_extra_outputs(audit_tool)

# add url via pico_set_program_url
example_auto_set_url(audit_tool)
