#include "../include/blinky.h"


#ifdef PULL_UP_INPUT
    #define BUTTON_PRESSED 0
#else
    #define BUTTON_PRESSED 1
#endif

void enable_interrupt(uint8_t gpio_pin);

void blinky_callback();

void blinky_init(BLINKY_VAR* ptBlinkyVar){

    led_init(&ptBlinkyVar->led_var);
    button_init(&ptBlinkyVar->button_var);
    enable_interrupt(ptBlinkyVar->button_var.button_pin);
    stdio_init_all();

}

void enable_interrupt(uint8_t gpio_pin){

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

    gpio_set_irq_enabled_with_callback(gpio_pin, event_mask, true, &blinky_callback);
}

void blinky_callback(uint gpio, uint32_t events){

    led_toggle();

}

int blinky_loop(BLINKY_VAR* ptBlinkyVar){

    while(1){

    }

}
