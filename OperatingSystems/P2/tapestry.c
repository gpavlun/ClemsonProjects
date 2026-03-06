#include "linkedlist.h"
#include "mythreads.h"
#include "evil.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <linux/types.h>
#include <assert.h>
#include <unistd.h>

LLheader *threadList;
LLheader *finishedList;
int threadCount;
//thData   *currentThread;

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
     
    threadList   = LLconstruct();
    finishedList = LLconstruct();
    assert( NOT threadMain() );

}



int threadMain(void){ 
    
    int returnValue = -1;

    IF( threadList )

        /**/ /*========================================================*/ /**/
        /**/ /*    allocate space for and create a thread structure    */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/    thData *thread = calloc(1, sizeof(thData));               /**/
        /**/    thread->threadID = threadCount;                           /**/
        /**/    threadCount++;                                            /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/



        /**/ /*========================================================*/ /**/
        /**/ /*         allocate space for and create a context        */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/    ucontext_t *context = calloc(1, sizeof(ucontext_t));      /**/
        /**/    thread->context = context;                                /**/
        /**/    getcontext(context);                                      /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/



        /**/ /*========================================================*/ /**/
        /**/ /*            add new thread to schedule list             */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/    LLappend(threadList, (void*)thread);                      /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/

        returnValue = thread->threadID;

    END

    return returnValue;

}

//function wrapper
void funcWrapper(thData *thread, thFuncPtr funcPtr, void *argPtr){

    threadExit( funcPtr(argPtr) );

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
    
    int returnValue = -1;

    IF( threadList )
        
        /**/ /*========================================================*/ /**/
        /**/ /*    allocate space for and create a thread structure    */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/    thData *thread = calloc(1, sizeof(thData));               /**/
        /**/    thread->threadID = threadCount;                           /**/
        /**/    threadCount++;                                            /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/



        /**/ /*========================================================*/ /**/
        /**/ /*         allocate space for and create a context        */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/    ucontext_t *context = calloc(1, sizeof(ucontext_t));      /**/
        /**/    thread->context = context;                                /**/
        /**/    getcontext(context);                                      /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/



        /**/ /*========================================================*/ /**/
        /**/ /*         allocate space for and create a new stack      */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/    thread->threadStack = calloc(1, STACK_SIZE);              /**/
        /**/    context->uc_stack.ss_size = STACK_SIZE;                   /**/
        /**/    context->uc_stack.ss_sp = thread->threadStack;            /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/
        
        

        /**/ /*========================================================*/ /**/
        /**/ /*      add new thread to schedule list and start it      */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/    LLinsert( threadList, (void*)thread,                      /**/
        /**/              0);                    /**/
        /**/                                                              /**/
        /**/    makecontext( context, (void(*)())(&funcWrapper),          /**/
        /**/                 3, thread, funcPtr, argPtr );                /**/
        /**/                                                              /**/
        /**/    threadYield();                                            /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/

        returnValue = thread->threadID;

    END

    return returnValue;

}

/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadYield                                                        │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Purpose: This function will allow the                                        │
│          current thread to yield back the CPU                                │
│          to the next mythreads                                               │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadYield(void){

    thData *currentThread = (thData *)(threadList->end->data);

    assert( currentThread );

    IF( threadList->start ISNT threadList->end )

        currentThread->state = SET;
        
        thData *nextThread = (thData *)LLremove(threadList, 0);
        nextThread->state = RUN;
        
        ucontext_t *currentContext = currentThread->context;
        ucontext_t *nextContext    = nextThread->context;
        
        LLappend(threadList, (void *)nextThread);       //atomize
        
        swapcontext(currentContext, nextContext);

    END
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
void threadJoin(int thread_id, void **result){

    

}

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
void threadExit(void *result){

    IF( NOT ((thData *)(threadList->end->data))->threadID )

        exit(0);

    ELSE

        thData *currentThread;
        currentThread = (thData *)LLremove( threadList, 
                                            threadList->entrycount-1);
        
        currentThread->state = FIN;
        LLappend(finishedList, (void *)currentThread); //atomize


        thData *nextThread;
        nextThread = (thData *)LLremove( threadList, 0 );
        LLappend(threadList, nextThread);
        swapcontext(currentThread->context, nextThread->context);

    END
}

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
