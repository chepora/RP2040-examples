#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "blinky.h"
#include "pico/stdlib.h"

#define LED_PIN         13
#define BUTTON_PIN      6
#define ALARM_DELAY_MS  10
#define BUTTON_SAMPLE   5


int main() {

    BLINKY_VAR used_params = {
        .led_var             = {.led_pin = LED_PIN},
        .button_var          = {.button_pin = BUTTON_PIN,
                                .button_samples_req = BUTTON_SAMPLE},
        .alarm_delay_ms      = ALARM_DELAY_MS,
    };

    blinky_init(&used_params);

    blinky_loop(&used_params);

}



