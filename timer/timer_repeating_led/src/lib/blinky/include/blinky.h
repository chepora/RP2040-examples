#ifndef BLINKY_H__
#define BLINKY_H_

#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "led.h"
#include "timer.h"

typedef struct BLINKY_VAR {

    LED_VAR     led_var;
    TIMER_VAR   timer_var;

} BLINKY_VAR;

void blinky_init(BLINKY_VAR* ptBlinkyVar);

int blinky_loop(BLINKY_VAR* ptBlinkyVar);

#endif