#ifndef PWM_H__
#define PWM_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "pitches.h"

void local_pwm_init(uint8_t pwm_pin, uint8_t max_duty_cycle);
void pwm_loop(uint8_t pwm_pin, uint8_t max_duty_cycle);

#endif