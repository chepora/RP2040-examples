add_subdirectory(lib)

add_executable(ws2812_poc
    main.c)


set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(ws2812_poc pico_stdlib hardware_pio pio)

# enable usb output, disable uart output
pico_enable_stdio_usb(ws2812_poc 0)
pico_enable_stdio_uart(ws2812_poc 1)

pico_add_extra_outputs(ws2812_poc)
