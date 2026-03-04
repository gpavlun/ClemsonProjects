#ifndef SCHED_SIM
#define SCHED_SIM

#define TRUE 1
#define FALSE 0

typedef struct{
	int arrived; //what time did it arrive?
	int length; //the length of the burst
	int priority; //the priority of the burst
	int remaining; //how much of the burst is left;
} burst_t;


typedef void (*init_func_ptr)();
typedef void (*burst_ready_func_ptr)(int, burst_t*);
typedef burst_t* (*next_burst_func_ptr)(int, burst_t**,int); //quantum, burst array, array length
typedef void (*burst_done_func_ptr)(int, burst_t *);


typedef struct {
	char *name;
	init_func_ptr init;
	burst_ready_func_ptr ready;
	next_burst_func_ptr next;
	burst_done_func_ptr done;
} scheduler_t;


void sim_init();
int sim_add_scheduler(scheduler_t *scheduler);
burst_t* load_burst_list(char *input_filename, int* num_bursts);
int sim_run(char *input_filename);

#endif