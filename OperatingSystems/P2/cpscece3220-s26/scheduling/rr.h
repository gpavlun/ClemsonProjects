
#ifndef RR_H
#define RR_H

#include <stdlib.h>
#include "schedsim.h"

void rr_init();
void rr_burst_ready(int quantum, burst_t *burst);
burst_t* rr_schedule_next_burst(int quantum, burst_t **bursts, int num_bursts);
void rr_burst_done(int quantum, burst_t *burst);



//tell the simulator which functions to use for the init, ready, and next actions
extern scheduler_t rr_scheduler;


#endif