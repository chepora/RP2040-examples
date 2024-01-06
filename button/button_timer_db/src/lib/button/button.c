#include "../include/button.h"

#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

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

    // set initial value to not pressed
    ptButtonVar->debounced_value    = false;
    ptButtonVar->button_press       = false;
    ptButtonVar->button_changed     = false;
   
}
