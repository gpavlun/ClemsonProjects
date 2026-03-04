
#ifndef FCFS_H
#define FCFS_H

#include <stdlib.h>
#include "schedsim.h"

void fcfs_init();
void fcfs_burst_ready(int quantum, burst_t *burst);
burst_t* fcfs_schedule_next_burst(int quantum, burst_t **bursts, int num_bursts);
void fcfs_burst_done(int quantum, burst_t *burst);



//tell the simulator which functions to use for the init, ready, and next actions
extern scheduler_t fcfs_scheduler;


#endif