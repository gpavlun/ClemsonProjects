#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/wait.h>


/*
all this does is fork off the process and loads the shim
*/
int main(int argc, char *argv[]){
    if(argc<2){
        printf("usage: ./leakcount ./your_program arg1 arg2\n");
        return 1;
    }else{
        int ChildID = fork();
        if(ChildID==-1){
            printf("ERROR: fork failed\n");
            return 1;
        }else if(!ChildID){
            if(setenv("LD_PRELOAD", "./mem_shim.so", 1)==-1){
                fprintf(stdout,"ERROR: setenv LD_PRELOAD failed\n");
                return 1;
            }
            if(execvp(argv[1], &(argv[1]))==-1){
                fprintf(stdout,"ERROR: exec failed\n");
                return 1;
            }
        }else{
            wait(NULL);
        }
    }
    return 0;
}
