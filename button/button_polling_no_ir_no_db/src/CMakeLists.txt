add_subdirectory(lib)

add_executable(button_poc
    main.c)

set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(button_poc pico_stdlib hardware_gpio blinky)

# enable usb output, disable uart output
pico_enable_stdio_usb(button_poc 0)
pico_enable_stdio_uart(button_poc 1)

pico_add_extra_outputs(button_poc)
