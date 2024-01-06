#include "../include/blinky.h"


#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

bool blinky_callback(struct repeating_timer *t);

void blinky_init(BLINKY_VAR* ptBlinkyVar){

    led_init(&ptBlinkyVar->led_var);
    ptBlinkyVar->timer_var.req_repeating_timer.callback = &blinky_callback;
    ptBlinkyVar->timer_var.req_repeating_timer.delay_us = ptBlinkyVar->timer_var.delay_us;
    timer_init(&ptBlinkyVar->timer_var);
    stdio_init_all();

}

bool blinky_callback(struct repeating_timer *t){

    led_toggle();
    return true;

}

int blinky_loop(BLINKY_VAR* ptBlinkyVar){

    while(1){

    }

}
