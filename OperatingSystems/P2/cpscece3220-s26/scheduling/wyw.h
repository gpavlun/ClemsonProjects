
#ifndef WYW_H
#define WYW_H

#include <stdlib.h>
#include "schedsim.h"

void wyw_init();
void wyw_burst_ready(int quantum, burst_t *burst);
burst_t* wyw_schedule_next_burst(int quantum, burst_t **bursts, int num_bursts);
void wyw_burst_done(int quantum, burst_t *burst);



//tell the simulator which functions to use for the init, ready, and next actions
extern scheduler_t wyw_scheduler;


#endif