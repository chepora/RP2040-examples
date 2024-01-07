#include "../include/button.h"

#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

static void button_disable_interrupt(BUTTON_VAR* ptButtonVar);

static void button_enable_interrupt(uint8_t gpio_pin, gpio_irq_callback_t button_callback);


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

    button_enable_interrupt(ptButtonVar->button_pin, ptButtonVar->button_callback);
   
}

static void button_enable_interrupt(uint8_t gpio_pin, gpio_irq_callback_t button_callback){

    // An interrupt can be generated for every GPIO pin in 4 scenarios:
    // Level High: the GPIO pin is a logical 1
    // GPIO_IRQ_LEVEL_HIGH = 0x2u,
    // Level Low: the GPIO pin is a logical 0
    // GPIO_IRQ_LEVEL_LOW = 0x1u,
    // Edge High: the GPIO has transitioned from a logical 0 to a logical 1
    // GPIO_IRQ_EDGE_RISE = 0x8u,
    // Edge Low: the GPIO has transitioned from a logical 1 to a logical 0
    // GPIO_IRQ_EDGE_FALL = 0x4u,

    uint32_t event_mask = 0;

    if (BUTTON_PRESSED)
    {
        event_mask = 0x4u; // GPIO_IRQ_EDGE_FALL

    }else event_mask = 0x8u; // GPIO_IRQ_EDGE_RISE 

    gpio_set_irq_enabled_with_callback(gpio_pin, event_mask, true, button_callback);

}

static void button_disable_interrupt(BUTTON_VAR* ptButtonVar){

    // An interrupt can be generated for every GPIO pin in 4 scenarios:
    // Level High: the GPIO pin is a logical 1
    // GPIO_IRQ_LEVEL_HIGH = 0x2u,
    // Level Low: the GPIO pin is a logical 0
    // GPIO_IRQ_LEVEL_LOW = 0x1u,
    // Edge High: the GPIO has transitioned from a logical 0 to a logical 1
    // GPIO_IRQ_EDGE_RISE = 0x8u,
    // Edge Low: the GPIO has transitioned from a logical 1 to a logical 0
    // GPIO_IRQ_EDGE_FALL = 0x4u,

    uint32_t event_mask = 0;

    if (BUTTON_PRESSED)
    {
        event_mask = 0x4u; // GPIO_IRQ_EDGE_FALL

    }else event_mask = 0x8u; // GPIO_IRQ_EDGE_RISE 

    gpio_set_irq_enabled_with_callback(ptButtonVar->button_pin, event_mask, false, ptButtonVar->button_callback);

}