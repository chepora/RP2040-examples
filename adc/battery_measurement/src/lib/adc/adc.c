#include "../include/adc.h"

adc_state_e local_adc_init(adc_params_t* pt_adc_params){

    adc_state_e adc_state = ADC_READ_ERROR;

    adc_init();

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(pt_adc_params->gpio);
    // Select ADC input 0 (GPIO26)
    adc_select_input(pt_adc_params->adc_nr);

    // placeholder
    adc_state = ADC_ALL_GOOD;

    return adc_state;
}

adc_state_e adc_read_and_print(){

    adc_state_e adc_state = ADC_READ_ERROR;

    // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
    // since the input was halfed through a double 100k-resistor dividor
    // we need to multiply it with 2 again -> 2 * 3.3 = 6.6
    const float conversion_factor = 6.6f / (1 << 12);
    uint16_t result = adc_read();

    printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);

    // placeholder
    adc_state = ADC_ALL_GOOD;

    return adc_state;
}