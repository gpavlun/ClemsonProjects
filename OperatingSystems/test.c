#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv){

    void *test = malloc(10);
    void *test1 = calloc(1,0);
    void *test0 = realloc(test,1000);
    //free(test0);

    return 0;
}
