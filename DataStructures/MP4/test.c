#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#include "llist.h"
#include "mem.h"

int main(void){
    mem_chunk_t *Memory;
    int units = sizeof(mem_chunk_t);
    int x[3];
    int y[3];
    x[0] = units;
    x[1] = 9 * units;
    x[2] = PAGESIZE;
    mem_chunk_t *freer;
    int i = 0;

    for(i=0;i<3;i++){
        printf("\nIteration x[%d]\n",i);
        printf("-------------------------\n");
        Memory = Mem_alloc(x[i]);
        y[i] = Memory;
        if(Memory==NULL){
            printf("NULL\n");
        }else{
            //printf("x[%d]:\n", i, x[i], Memory);
            //printf("desired = %d bytes at %X\n", x[i], Memory);
            //printf("actual  = %d bytes at %X\n", (((Memory-1)->num_units) - 1)*sizeof(mem_chunk_t), Memory);
        }

    }
    printf("===================FREE====================\n");
    for(i=0;i<3;i++){
        Mem_free((void *)y[i]);
    }
    


    return 1;
}