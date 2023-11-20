add_executable(blackwhitelist blackwhitelist.c)

# pull in common dependencies
target_link_libraries(blackwhitelist pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(blackwhitelist)
pico_enable_stdio_usb(blackwhitelist 1)

# add url via pico_set_program_url
example_auto_set_url(blackwhitelist)
