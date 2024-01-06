#ifndef LED_H__
#define LED_H_

#include <stdint.h>
#include "pico/stdlib.h"

typedef struct LED_VAR {

    uint8_t     led_pin;

} LED_VAR;

void led_init(LED_VAR* ptLedVar);
void led_on(uint8_t led_pin);
void led_off(uint8_t led_pin);
void led_toggle();
void led_blink(uint8_t led_pin, uint32_t blink_time_ms);

#endif