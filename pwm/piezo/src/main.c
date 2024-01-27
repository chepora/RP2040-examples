#include <stdio.h>

#include "pwm.h"

#define BUZZER_PIN 26
#define MAX_DUTY_CYCLE 100


int main() {

    stdio_init_all(); // UART setup for both input and output

    local_pwm_init(BUZZER_PIN, MAX_DUTY_CYCLE);

    pwm_loop(BUZZER_PIN, MAX_DUTY_CYCLE);

}



