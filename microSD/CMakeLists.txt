add_executable(microSD
        microSD.c
        )


# pull in common dependencies
target_link_libraries(microSD 
                        pico_stdlib 
                        hardware_spi 
                        pico_multicore  
                        FatFs_SPI
                        )
                        
# Tell CMake where to find other source code
add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)

# create map/bin/hex file etc.
pico_add_extra_outputs(microSD)

# add url via pico_set_program_url
example_auto_set_url(microSD)

#enable usb output
pico_enable_stdio_usb(microSD 1)
pico_enable_stdio_uart(microSD 0)