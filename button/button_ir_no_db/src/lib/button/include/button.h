#ifndef BUTTON_H__
#define BUTTON_H_

#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define PULL_UP_INPUT
#define DISABLE_HYSTERESIS

typedef struct BUTTON_VAR {

    uint8_t     button_pin;

} BUTTON_VAR;

void button_init(BUTTON_VAR* ptButtonVar);

#endif