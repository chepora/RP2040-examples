#include "../include/timer.h"


void timer_init(TIMER_VAR* ptTimerVar){

    add_repeating_timer_ms(ptTimerVar->req_repeating_timer.delay_us, ptTimerVar->req_repeating_timer.callback, NULL, &ptTimerVar->running_repeating_timer);

}
