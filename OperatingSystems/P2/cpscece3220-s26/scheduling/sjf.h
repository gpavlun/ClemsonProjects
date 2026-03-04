
#ifndef SJF_H
#define SJF_H

#include <stdlib.h>
#include "schedsim.h"

void sjf_init();
void sjf_burst_ready(int quantum, burst_t *burst);
burst_t* sjf_schedule_next_burst(int quantum, burst_t **bursts, int num_bursts);
void sjf_burst_done(int quantum, burst_t *burst);



//tell the simulator which functions to use for the init, ready, and next actions
extern scheduler_t sjf_scheduler;


#endif