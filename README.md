# RP2040-examples
Collection of small examples using the RP2040 and pico-sdk.

All examples are independent of another and all depend on [RPi Pico SDK V1.5.1](https://github.com/raspberrypi/pico-sdk)

## List of Examples

- [`adc`](https://github.com/chepora/RP2040-examples/tree/main/adc)
    - [`battery_measurement`](https://github.com/chepora/RP2040-examples/tree/main/adc/battery_measurement): ADC reading battery voltage

- [`button`](https://github.com/chepora/RP2040-examples/tree/main/button)
    - [`button_polling_no_ir_no_db`](https://github.com/chepora/RP2040-examples/tree/main/button/button_polling_no_ir_no_db): Most Simple Button and LED Example (no interrupt, no debouncing)
    - [`button_ir_no_db`](https://github.com/chepora/RP2040-examples/tree/main/button/button_ir_no_db): Simple Button with Interrupt and LED Example (no debouncing)
    - [`button_timer_db`](https://github.com/chepora/RP2040-examples/tree/main/button): Simple Button with Interrupt, Debouncing and LED Example

- [`i2c`](https://github.com/chepora/RP2040-examples/tree/main/i2c)
    - [`bno055`](https://github.com/chepora/RP2040-examples/tree/main/i2c/bno055): First steps with the BNO055

- [`led`](https://github.com/chepora/RP2040-examples/tree/main/led)
    - [`WS2812`](https://github.com/chepora/RP2040-examples/tree/main/led/WS2812): driving a WS2812 LED using PIO

- [`pio`](https://github.com/chepora/RP2040-examples/tree/main/pio)
    - [`WS2812`](https://github.com/chepora/RP2040-examples/tree/main/led/WS2812): driving a WS2812 LED using PIO

- [`pwn`](https://github.com/chepora/RP2040-examples/tree/main/pwm)
    - [`WS2812`](https://github.com/chepora/RP2040-examples/tree/main/pwm/piezo): Simple PWM over GPIO

- [`timer`](https://github.com/chepora/RP2040-examples/tree/main/timer)
    - [`timer_repeating_led`](https://github.com/chepora/RP2040-examples/tree/main/timer/timer_repeating_led): A repeating timer that toggles a LED


## License

Licensed under either of

    - Apache License, Version 2.0 (LICENSE-APACHE or http://www.apache.org/licenses/LICENSE-2.0)
    - MIT license (LICENSE-MIT or http://opensource.org/licenses/MIT)

at your option.

Parts that were taken from the Raspberry Pi (Trading) Ltd.'s examples are under

    - 	BSD-3-Clause(BSD-3-Clause or https://opensource.org/license/BSD-3-clause/) Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
