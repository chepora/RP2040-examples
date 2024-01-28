#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

#include "adc.h"

#define ADC_PIN     26
#define ADC_INST    0


int main() {

    stdio_init_all();

    adc_state_e adc_state = ADC_READ_ERROR;


    adc_params_t adc_params = { .gpio = ADC_PIN,
                                .adc_nr = ADC_INST,};

    printf("ADC Example, measuring GPIO%d\n", adc_params.gpio);

    adc_state = local_adc_init(&adc_params);

    while(1) {

        adc_state = adc_read_and_print();
        sleep_ms(500);
    }
}
