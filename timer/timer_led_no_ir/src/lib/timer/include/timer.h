#ifndef LED_H__
#define LED_H_

#include <stdint.h>
#include "pico/stdlib.h"

typedef struct TIMER_VAR {

    //    struct repeating_timer {
    //    int64_t delay_us;
    //    alarm_pool_t *pool;
    //    alarm_id_t alarm_id;
    //    repeating_timer_callback_t callback;
    //    void *user_data;
    //};

    int64_t delay_us;
    repeating_timer_t req_repeating_timer;
    repeating_timer_t running_repeating_timer;


} TIMER_VAR;    

void timer_init(TIMER_VAR* ptTimerVar);

#endif