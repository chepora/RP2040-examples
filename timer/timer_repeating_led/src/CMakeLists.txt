add_subdirectory(lib)

add_executable(timer_poc
    main.c)

set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(timer_poc pico_stdlib hardware_gpio blinky)

# enable usb output, disable uart output
pico_enable_stdio_usb(timer_poc 0)
pico_enable_stdio_uart(timer_poc 1)

pico_add_extra_outputs(timer_poc)
