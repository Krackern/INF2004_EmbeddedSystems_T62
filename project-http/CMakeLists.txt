add_executable(http-main main.c)

# pull in common dependencies
target_link_libraries(http-main     
                        pico_stdlib    
                        hardware_pwm
                        pico_http_client
                        # pico_unique_id 
                        # tinyusb_device 
                        # tinyusb_board 
                        # FatFs_SPI
                        )

# create map/bin/hex file etc.
pico_enable_stdio_uart(http-main 1)
pico_add_extra_outputs(http-main)
pico_enable_stdio_usb(http-main 1)

# add url via pico_set_program_url
example_auto_set_url(http-main)

#set(OUTPUT_NAME picow_basic_request)

