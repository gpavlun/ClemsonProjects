#include "evil.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include "mythreads.h"

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


void *foo(void *){
  fprintf(stdout, "I am thread\n");
  return 0;
}


START

  threadInit();

  threadCreate(foo, NULL);




FINISH
