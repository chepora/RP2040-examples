#include "../include/pwm.h"

uint slice_num;

static uint32_t clock;


void local_pwm_init(uint8_t pwm_pin, uint8_t max_duty_cycle) {

    clock = clock_get_hz(clk_sys);

    // PWM setup
    float clkdiv = 255.0;
    gpio_set_function(pwm_pin, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(pwm_pin);
    pwm_set_clkdiv(slice_num, clkdiv);
    pwm_set_wrap(slice_num, max_duty_cycle);  
    pwm_set_enabled(slice_num, true);

}

void set_frequency(uint8_t pwm_pin, float freq){
    
    float divider = (float) clock / (freq * 10000.0);
    pwm_set_clkdiv(slice_num, divider);
    pwm_set_wrap(slice_num, 10000);
    pwm_set_gpio_level(pwm_pin, 5000);

}

void pwm_loop(uint8_t pwm_pin, uint8_t max_duty_cycle){

    int change = 5;    
    int dutyPercent = 0;
    float clkdiv = 255.0;
    float frequencyDividerChange = 30.0;

    while(1){

        set_frequency(pwm_pin, NOTE_C5);
        sleep_ms(128);
        set_frequency(pwm_pin, NOTE_CS5);
        sleep_ms(128);
        set_frequency(pwm_pin, NOTE_D5);
        sleep_ms(128);
        set_frequency(pwm_pin, NOTE_DS5);
        sleep_ms(128);
        set_frequency(pwm_pin, NOTE_E5);
        sleep_ms(128);
        set_frequency(pwm_pin, NOTE_F5);
        sleep_ms(128);
        set_frequency(pwm_pin, NOTE_FS5);
        sleep_ms(128);
        set_frequency(pwm_pin, NOTE_G5);
        sleep_ms(128);

        sleep_ms(1000);

        set_frequency(pwm_pin, NOTE_C4);
        sleep_ms(160);
        set_frequency(pwm_pin, NOTE_AS4);
        sleep_ms(160);
        set_frequency(pwm_pin, NOTE_C5);
        sleep_ms(160);

        sleep_ms(2000);

        set_frequency(pwm_pin, NOTE_A4);
        sleep_ms(512);
        set_frequency(pwm_pin, NOTE_AS4);
        sleep_ms(256);

        sleep_ms(2000);


    }

    //while (1) {
    //dutyPercent += change;
    //if (dutyPercent >= max_duty_cycle) {
    //  dutyPercent = 0;
    //  if (frequencyDividerChange > 0) {
    //    clkdiv -= frequencyDividerChange;
    //    pwm_set_clkdiv(slice_num, clkdiv);
    //  }
//
    //}
    //// when at max, go directly back to zero
    //pwm_set_gpio_level(pwm_pin, dutyPercent);
    //sleep_ms(200);
    //}


}

