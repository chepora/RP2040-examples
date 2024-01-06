#ifndef BUTTON_H__
#define BUTTON_H_

#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define PULL_UP_INPUT
#define DISABLE_HYSTERESIS

typedef struct BUTTON_VAR {

    uint8_t     button_pin;
    bool        button_press;
    bool        button_changed;
    bool        debounced_value;
    bool        raw_reading;
    uint8_t     button_samples_req;
    uint8_t     button_samples_to_do;

} BUTTON_VAR;

void button_init(BUTTON_VAR* ptButtonVar);

#endif