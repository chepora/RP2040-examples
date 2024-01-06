#include "../include/blinky.h"


#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

void blinky_init(BLINKY_VAR* ptBlinkyVar){

    led_init(&ptBlinkyVar->led_var);
    button_init(&ptBlinkyVar->button_var);
    stdio_init_all();

}

int blinky_loop(BLINKY_VAR* ptBlinkyVar){

    while(true){

        if(BUTTON_PRESSED == gpio_get(ptBlinkyVar->button_var.button_pin)){
            led_on(ptBlinkyVar->led_var.led_pin);
        }else
        {
            led_off(ptBlinkyVar->led_var.led_pin);
        }

        sleep_ms(250);

    }

}
