add_subdirectory(lib)

add_executable(adc_poc
    main.c)

set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(adc_poc pico_stdlib hardware_gpio adc)

# disable usb output, enable uart output
pico_enable_stdio_usb(adc_poc 0)
pico_enable_stdio_uart(adc_poc 1)

pico_add_extra_outputs(adc_poc)
