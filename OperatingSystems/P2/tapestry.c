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


/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadInit                                                         │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadInit(void){
     
    threadList   = LLconstruct();
    finishedList = LLconstruct();
    assert( NOT threadMain() );

}
/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadInit                                                         │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadDebrief(void){

    ListDestruct(threadList);
    ListDestruct(finishedList);
    exit(0);

}
/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadInit                                                         │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void ListDestruct(LLheader *Header){

    int CurrentNode;
    int NodeCount = Header->entrycount;
    LLnode *ListPosition = Header->start;
    LLnode *ListPrev = NULL;
    
    FOR(CurrentNode, 0, NodeCount)

        IF(ListPosition->next)

            ListPrev = ListPosition;
            ListPosition = ListPosition->next;

            IF(ListPosition->prev->data)

                IF( thPtr(ListPrev->data)->context )
                    free( thPtr(ListPrev->data)->context );
                END

                IF( thPtr(ListPrev->data)->threadStack )
                    free( thPtr(ListPrev->data)->threadStack );
                END

                free( ListPosition->prev->data );

            END 

            free(ListPosition->prev);
        
        ELSE
            IF(ListPosition->data)

                free(ListPosition->data);
            
            END

            free(ListPosition);
        
        END

    END

    free(Header);
}










        /**/ /*========================================================*/ /**/
        /**/ /*                                                        */ /**/
        /**/ /*========================================================*/ /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/                                                              /**/
        /**/ /*========================================================*/ /**/



/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadInit                                                         │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
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


/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadInit                                                         │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
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
│ Description: This function is meant to be called by a currently running      │
│              thread from my library, or by your main function, which is      │
│              considered a thread for scheduling purposes. The implementation │
│              is very simple, the code will dequeue the next node from the    │
│              schedule queue and the reappend it at the end, switching to     │
│              that node as it does so. This is done through a simple context  │
│              switch at the end of the function. This function must certainly │
│              be atomic, or have interrupts disabled, since it can cause      │
│              severe harm or undefined behavior if there is a context switch  │
│              that occurs during another switch.                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadYield(void){

    IF( threadList )

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
        
    END
}

/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadInit                                                         │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadJoin(int thread_id, void **result){
    
    IF( threadList )
    
        



    END
}

/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadInit                                                         │
│                                                                              │
│ Inputs: void                                                                 │
│                                                                              │
│ Outputs: void                                                                │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadExit(void *result){

    IF( threadList )

        IF( NOT thPtr(threadList->end->data)->threadID )

            threadDebrief();

        ELSE

            /**/ /*========================================================*/ /**/
            /**/ /*        get currently running thread from list          */ /**/
            /**/ /*========================================================*/ /**/
            /**/                                                              /**/
            /**/    thData *currentThread;                                    /**/
            /**/    currentThread = (thData *)LLremove( threadList,           /**/
            /**/                                threadList->entrycount-1);    /**/
            /**/                                                              /**/
            /**/ /*========================================================*/ /**/



            /**/ /*========================================================*/ /**/
            /**/ /*            add current thread to finished list         */ /**/
            /**/ /*========================================================*/ /**/
            /**/                                                              /**/
            /**/    currentThread->returnValue = result;                      /**/
            /**/    currentThread->state = FIN;                               /**/   //atomize
            /**/    LLappend(finishedList, (void *)currentThread);            /**/
            /**/                                                              /**/
            /**/ /*========================================================*/ /**/
            
            
            

            /**/ /*========================================================*/ /**/
            /**/ /*           switch to next running thread                */ /**/
            /**/ /*========================================================*/ /**/
            /**/                                                              /**/
            /**/    thData *nextThread;                                       /**/
            /**/    nextThread = (thData *)LLremove( threadList, 0 );         /**/
            /**/    LLappend(threadList, nextThread);                         /**/
            /**/    swapcontext(currentThread->context, nextThread->context); /**/
            /**/                                                              /**/
            /**/ /*========================================================*/ /**/

        END

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
