#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "blinky.h"
#include "pico/stdlib.h"

#define LED_PIN         13
#define TIMER_DELAY_MS  500

int main() {

    BLINKY_VAR used_params = {
        .led_var        = {.led_pin = LED_PIN},
        .timer_var      = {.delay_us = TIMER_DELAY_MS},
    };

    blinky_init(&used_params);

    blinky_loop(&used_params);

}



