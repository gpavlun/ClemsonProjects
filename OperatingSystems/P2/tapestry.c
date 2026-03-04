#include "linkedlist.h"
#include "mythreads.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ucontext.h>
#include <ucontext.h>

LLheader *threadList;

/*──────────────────────────────────────┐
│Function: threadInit                   │
├───────────────────────────────────────┤
│Inputs: void                           │
│Outputs: void                          │
│                                       │
│Purpose: This function intializes the  │
│mythreads library.                     │
│                                       │
│                                       │
└──────────────────────────────────────*/
void threadInit(void){
     
    threadList = LLconstruct();

}

//function wrapper
void *funcWrapper(thData *thread, thFuncPtr funcPtr, void *argPtr){

    thread->state = 1;
    void *funcReturn = funcPtr(argPtr);
    thread->state = 0;
    return funcReturn;

}




/*──────────────────────────────────────┐
│Function: threadCreate                 │
├───────────────────────────────────────┤
│Inputs: thFuncPtr funcPtr, void *argPtr│
│Outputs: int                           │
│                                       │
│Purpose: This function creates a new   │
│thread for the mythreads library.      │
│                                       │
│                                       │
└──────────────────────────────────────*/
int threadCreate(thFuncPtr funcPtr, void *argPtr){ 
    
    if(threadList){
        thData *thread = (thData *)calloc(1, sizeof(thData));
        thread->threadID = threadList->entrycount - 1;

        ucontext_t *context = calloc(1, sizeof(ucontext_t));
        thread->context = context;
        getcontext(context);
        
        thread->threadStack = calloc(1, STACK_SIZE);
        context->uc_stack.ss_size = STACK_SIZE;
        context->uc_stack.ss_sp = thread->threadStack;
        
        LLappend(threadList, (void*)thread);

        makecontext(context, funcWrapper, 3, &thread, funcPtr, argPtr);

        return thread->threadID;
    }else{
        return -1;
    }
  
}

/*──────────────────────────────────────┐
│Function: threadYield                  │
├───────────────────────────────────────┤
│Inputs: void                           │
│Outputs: void                          │
│                                       │
│Purpose: This function will allow the  │
│current thread to yield back the CPU   │
│to the next mythreads                  │
│                                       │
└──────────────────────────────────────*/
void threadYield(void){
    static LLnode *currentThread;
    
    if(!currentThread){
        currentThread = threadList->start;
        if(!currentThread){
            fprintf(stderr,"no thread active\n");
            exit(1);
        }
    }

    if(threadList->start-threadList->end){
        ucontext_t currentContext = *((thData *)(currentThread->data))->context;
        ucontext_t nextContext;
        if(currentThread->next){
            nextContext = *((thData *)(currentThread->next->data))->context;
        }else{
            nextContext = *((thData *)(threadList->start->data))->context;
        }

        swapcontext(&currentContext, &nextContext);
    }
}

/*──────────────────────────────────────┐
│Function: threadJoin                   │
├───────────────────────────────────────┤
│Inputs: int thread_ID, void**result    │
│Outputs: void                          │
│                                       │
│Purpose: This function will allow a    │
│running thread to rejoin with the main │
│process.                               │
│                                       │
└──────────────────────────────────────*/
void threadJoin(int thread_id, void **result) {}

/*──────────────────────────────────────┐
│Function: threadExit                   │
├───────────────────────────────────────┤
│Inputs: void *result                   │
│Outputs: void                          │
│                                       │
│Purpose: This function will close the  │
│current thread and rejoin with main. If│
│main thread is closed, this will end   │
│the program.                           │
│                                       │
└──────────────────────────────────────*/
void threadExit(void *result) {}

// mutex lock types and functions.
struct mutexlock; // opaque type -- you need to implement this in your source
                  // file

mutexlock_t *lockCreate(void);
void lockDestroy(mutexlock_t *lock);
void threadLock(mutexlock_t *lock);
void threadUnlock(mutexlock_t *lock);

// condition variable types and functions
struct condvar; // opaque type -- you need to implement this in your source file
typedef struct condvar condvar_t;

extern condvar_t *condvarCreate(void);
extern void condvarDestroy(condvar_t *cv);
extern void threadWait(mutexlock_t *lock, condvar_t *cv);
extern void threadSignal(mutexlock_t *lock, condvar_t *cv);

// this
extern int interruptsAreDisabled;
