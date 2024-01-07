#include "../include/timer.h"

TIMER_VAR* ptLocalTimerVar;


void timer_init(TIMER_VAR* ptTimerVar){

    ptLocalTimerVar = ptTimerVar;
}

void timer_start(){

    add_repeating_timer_ms(ptLocalTimerVar->delay_ms, ptLocalTimerVar->callback, NULL, &ptLocalTimerVar->repeating_timer);

}

void timer_reset(TIMER_VAR* ptTimerVar){


}
