
#ifndef PRIORITY_H
#define PRIORITY_H

#include <stdlib.h>
#include "schedsim.h"

void pr_init();
void pr_burst_ready(int quantum, burst_t *burst);
burst_t* pr_schedule_next_burst(int quantum, burst_t **bursts, int num_bursts);
void pr_burst_done(int quantum, burst_t *burst);



//tell the simulator which functions to use for the init, ready, and next actions
extern scheduler_t pr_scheduler;


#endif