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
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   none                                                                       │
│                                                                              │
│ Return:                                                                      │
│                                                                              │
│   none                                                                       │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│       This function initialized the threading library. It does this by       │
│   creating two linked lists. The first one is a queue containing the         │
│   currently running threads and the second one is a simple list of the       │
│   finished threads in the program. It then creates a thread from main and    │
│   adds it to the currently running list.                                     │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadInit(void){
     
    threadList   = LLconstruct();
    finishedList = LLconstruct();
    assert( NOT threadMain() );

}
/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadDebrief                                                      │
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   none                                                                       │
│                                                                              │
│ Return:                                                                      │
│                                                                              │
│   none                                                                       │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│       This function is called when the main thread calls threadExit. It      │
│   works by destructing the active thread list and the finished thread list,  │
│   then using te exit system call to terminate the program.                   │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void threadDebrief(void){

    ListDestruct(threadList);
    ListDestruct(finishedList);
    exit(0);

}
/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: ListDestruct                                                       │
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   LLheader *Header, this the header of a linked list from linkedlist.h       │
│                                                                              │
│ Outputs:                                                                     │
│                                                                              │
│   none                                                                       │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│       The LLdestruct function I wrote in linkedlist.h does not free the      │
│   internally allocated structures in the thread data structure, so I         │
│   created this function to handle clean up of the lists. Just has an         │
│   additional step where it frees the context and the stack.                  │
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
│ Function: threadMain                                                         │
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   none                                                                       │
│                                                                              │
│ Return:                                                                      │
│                                                                              │
│   int, main ID on success, -1 on failure                                     │
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

/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: funcWrapper                                                        │
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   1. thData *thread, pointer to a thread data structure                      │
│   1. thFuncPtr funcPtr, pointer to the thread function                       │
│   2. void *argPtr, pointer the thread function argument                      │
│                                                                              │
│ Return:                                                                      │
│                                                                              │
│   none                                                                       │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│       This function serves a simple wrapper for thread functions. When the   │
│   thread function returns, it calls threadExit on that thread to clean it    │
│   up.                                                                        │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────*/
void funcWrapper(thData *thread, thFuncPtr funcPtr, void *argPtr){

    threadExit( funcPtr(argPtr) );

}


/*─────────────────────────────────────────────────────────────────────────────┐
│ Function: threadCreate                                                       │
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   1. thFuncPtr funcPtr, pointer to the thread function                       │
│   2. void *argPtr, pointer the thread function argument                      │
│                                                                              │
│ Retrun:                                                                      │
│                                                                              │
│   int, thread ID on success, -1 on failure                                   │
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
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   none                                                                       │
│                                                                              │
│ Outputs:                                                                     │
│                                                                              │
│   none                                                                       │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│       This function is meant to be called by a currently running thread from │
│   my library, or by your main function, which is considered a thread for     │
│   scheduling purposes. The implementation is very simple, the code will      │
│   dequeue the next node from the schedule queue and the reappend it at the   │
│   end, switching to that node as it does so. This is done through a simple   │
│   context switch at the end of the function. This function must certainly be │
│   atomic, or have interrupts disabled, since it can cause severe harm or     │
│   undefined behavior if there is a context switch that occurs during another │
│  switch.                                                                     │
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
│ Function: threadJoin                                                         │
├──────────────────────────────────────────────────────────────────────────────┤
│ Parameters:                                                                  │
│                                                                              │
│   1. int thread_id, ID of the thread to wait on                              │
│   2. void **result, pointer to the return pointer of the thread function     │
│                                                                              │
│ Return                                                                       │
│                                                                              │
│   none                                                                       │
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
│ Function: threadExit                                                         │
├──────────────────────────────────────────────────────────────────────────────┤
│ Inputs:                                                                      │
│                                                                              │
│   void *result, pointer to the return value of a thread function             │
│                                                                              │
│ Outputs:                                                                     │
│                                                                              │
│   none                                                                       │
│                                                                              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Description:                                                                 │
│                                                                              │
│       This function allows a thread to rejoin the main thread, if the main   │
│   thread calls this funciton, it will deconstruct the library and terminate  │
│   the program. This function works by removing the currently running thread  │
│   from the list of active threads, appending itself to the end of the list   │
│   of finished threads, and then context swapping back to the next available  │
│   thread in the schedule queue. If the ID number of the thread is zero, then │
│   the function identifies the thread as main and calls the threadDebrief     │
│   function, which breaks down the library and frees the memory.              │
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
