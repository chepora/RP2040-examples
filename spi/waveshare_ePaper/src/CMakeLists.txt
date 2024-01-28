add_subdirectory(lib)

add_executable(spi_poc
    main.c)


set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(spi_poc pico_stdlib spi epaper)

# enable usb output, disable uart output
pico_enable_stdio_usb(spi_poc 0)
pico_enable_stdio_uart(spi_poc 1)

pico_add_extra_outputs(spi_poc)
