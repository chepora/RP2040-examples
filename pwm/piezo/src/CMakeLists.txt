add_subdirectory(lib)

add_executable(pwm_poc
    main.c)


set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(pwm_poc pico_stdlib hardware_gpio hardware_pwm pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(pwm_poc 0)
pico_enable_stdio_uart(pwm_poc 1)

pico_add_extra_outputs(pwm_poc)
