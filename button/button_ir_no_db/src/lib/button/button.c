#include "../include/button.h"

void button_init(BUTTON_VAR* ptButtonVar){

    #ifdef DISABLE_HYSTERESIS
        // Schmitt trigger hysteresis is enabled on all GPIOs by default
        // to see why debouncing is truly necessary:
        gpio_set_input_hysteresis_enabled(ptButtonVar->button_pin, false);
    #endif 

    gpio_init(ptButtonVar->button_pin);
    gpio_set_dir(ptButtonVar->button_pin, GPIO_IN);

    #ifdef PULL_UP_INPUT
        // if button sits between IO and GND:
        gpio_pull_up(ptButtonVar->button_pin);

    #else
        // if button sits between IO and POWER:
        gpio_pull_down(ptButtonVar->button_pin);
    #endif 
   
}
