#include "../include/blinky.h"


#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

void blinky_irs_callback(uint gpio, uint32_t event_mask);
bool blinky_timer_callback(struct repeating_timer *t);

void blinky_init(BLINKY_VAR* ptBlinkyVar){

    // add callbacks to module structs
    ptBlinkyVar->button_var.button_callback = &blinky_irs_callback;
    ptBlinkyVar->timer_var.callback = &blinky_timer_callback;

    led_init(&ptBlinkyVar->led_var);
    button_init(&ptBlinkyVar->button_var);
    timer_init(&ptBlinkyVar->timer_var);
    stdio_init_all();

}

void blinky_irs_callback(uint gpio, uint32_t event_mask){    

    timer_start();
    gpio_set_irq_enabled(gpio, event_mask, false);

}

bool blinky_timer_callback(struct repeating_timer *t){

    led_toggle();
    return true;

}

int blinky_loop(BLINKY_VAR* ptBlinkyVar){


    while(1){

    }

}
