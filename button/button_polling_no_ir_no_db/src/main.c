#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "blinky.h"
#include "pico/stdlib.h"

#define LED_PIN     13
#define BUTTON_PIN  6

int main() {

    BLINKY_VAR used_params = {
        .led_var       = {.led_pin = LED_PIN},
        .button_var    = {.button_pin = BUTTON_PIN},
    };

    blinky_init(&used_params);

    blinky_loop(&used_params);

}