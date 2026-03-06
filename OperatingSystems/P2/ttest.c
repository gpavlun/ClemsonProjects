#include "evil.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include "mythreads.h"
#include <linux/types.h>
#include <unistd.h>
#include "linkedlist.h"

int interruptsAreDisabled;
extern LLheader *threadList;
extern int threadCount;

void deez(void){
  ucontext_t func, Return;

  int x = 0;
  void *funcParameter;

  // function def
  char first = 1;
  getcontext(&func);  
  IF(!first)
    getcontext(&func);
    (*((int *)funcParameter))++;
    setcontext(&Return);
  ELSE
    first--;
  END


  printf("before call:\n\tx = %d\n", x);
  funcParameter = &x;
  swapcontext(&Return, &func);
  printf("after call:\n\tx = %d\n", x);
}


void *foo(int *ID){
  int i = 0;
  int I = *ID - 1;

  printf("thread[%d] %d\n",I,i);
  i++;

  threadYield();

  printf("thread[%d] %d\n",I,i);
  i++;

  threadExit(NULL);

  return NULL;
}



MAIN
  int i = 0;

  threadInit();

  printf("\t[[main %d]]\n", i);
  i++;

  threadCreate((thFuncPtr)(&foo), (void *)(&threadCount));

  printf("\t[[main %d]]\n", i);
  i++;

  threadCreate((thFuncPtr)(&foo), (void *)(&threadCount));

  printf("\t[[main %d]]\n", i);
  i++;

  threadYield();

  printf("\t[[main %d]]\n", i);
  i++;



FINISH
