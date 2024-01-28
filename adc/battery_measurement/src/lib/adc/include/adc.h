#ifndef ADC_H__
#define ADC_H_

#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

typedef enum {
    ADC_ALL_GOOD    = 0x00,
    ADC_WRITE_ERROR = 0x0F,
    ADC_READ_ERROR  = 0xF0,
} adc_state_e;

typedef struct {

    uint8_t gpio;
    uint8_t adc_nr;

} adc_params_t;

adc_state_e local_adc_init(adc_params_t* pt_adc_params);

adc_state_e adc_read_and_print(void);

#endif