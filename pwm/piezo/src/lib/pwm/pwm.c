#include "../include/pwm.h"

uint slice_num;


void local_pwm_init(uint8_t pwm_pin, uint8_t max_duty_cycle) {

    // PWM setup
    float clkdiv = 255.0;
    gpio_set_function(pwm_pin, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(pwm_pin);
    pwm_set_clkdiv(slice_num, clkdiv);
    pwm_set_wrap(slice_num, max_duty_cycle);  
    pwm_set_enabled(slice_num, true);

}

void pwm_loop(uint8_t pwm_pin, uint8_t max_duty_cycle){

    int change = 5;    
    int dutyPercent = 0;
    float clkdiv = 255.0;
    float frequencyDividerChange = 30.0;

    while (1) {
    dutyPercent += change;
    if (dutyPercent >= max_duty_cycle) {
      dutyPercent = 0;
      if (frequencyDividerChange > 0) {
        clkdiv -= frequencyDividerChange;
        pwm_set_clkdiv(slice_num, clkdiv);
      }

    }
    // when at max, go directly back to zero
    pwm_set_gpio_level(pwm_pin, dutyPercent);
    sleep_ms(200);
    }

}

