add_subdirectory(lib)

add_executable(bno055_poc
    main.c)

set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(bno055_poc pico_stdlib hardware_gpio bno055)

# disable usb output, enable uart output
pico_enable_stdio_usb(bno055_poc 0)
pico_enable_stdio_uart(bno055_poc 1)

pico_add_extra_outputs(bno055_poc)
