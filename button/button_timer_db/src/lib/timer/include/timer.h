#ifndef LED_H__
#define LED_H_

#include <stdint.h>
#include "pico/stdlib.h"

typedef struct TIMER_VAR {

    // the pico-sdk defines: 
    //    struct repeating_timer {
    //    int64_t delay_us;
    //    alarm_pool_t *pool;
    //    alarm_id_t alarm_id;
    //    repeating_timer_callback_t callback;
    //    void *user_data;
    //};

    int64_t delay_ms;
    repeating_timer_callback_t callback;
    repeating_timer_t repeating_timer;

} TIMER_VAR;    

void timer_init(TIMER_VAR* ptTimerVar);
void timer_start();
void timer_reset(TIMER_VAR* ptTimerVar);

#endif