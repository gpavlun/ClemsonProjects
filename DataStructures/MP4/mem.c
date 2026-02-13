/* mem.c A template
 * Gregory Pavlunenko, Firstborn of Alexey Pavlunenko, Rightful heir to the throne of Arstotzka
 * gpavlun (C25220578?)
 * gpavlun
 * Lab4: Dynamic Memory Allocation
 * ECE 2230, Fall 2025
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <limits.h>

#include "mem.h"

// Global variables required in mem.c only
static int Coalescing = FALSE;      // default FALSE. TRUE if memory returned to free list is coalesced 
static int SearchPolicy = FIRST_FIT;   // default FIRST_FIT.  Can change to BEST_FIT
// NEVER use DummyChunk in your allocation or free functions!!
static mem_chunk_t DummyChunk = {0, &DummyChunk, &DummyChunk,0,0};
static mem_chunk_t *Rover = &DummyChunk;   // one time initialization

static int NumPages = 0;
static int NumSbrkCalls = 0;

// private function prototypes
void mem_validate(void);

/* function to request 1 or more pages from the operating system.
 *
 * new_bytes must be the number of bytes that are being requested from
 *           the OS with the sbrk command.  It must be an integer 
 *           multiple of the PAGESIZE
 *
 * returns a pointer to the new memory location.  If the request for
 * new memory fails this function simply returns NULL, and assumes some
 * calling function will handle the error condition.  Since the error
 * condition is catastrophic, nothing can be done but to terminate 
 * the program.
 */
mem_chunk_t *morecore(int new_bytes) 
{
    char *cp;
    mem_chunk_t *new_p;
    // preconditions that must be true for all designs
    //assert(new_bytes % PAGESIZE == 0 && new_bytes > 0);
    //assert(PAGESIZE % sizeof(mem_chunk_t) == 0);
    cp = sbrk(new_bytes);
    if (cp == (char *) -1)  /* no space available */
        return NULL;
    new_p = (mem_chunk_t *) cp;
    // Code to count the number of calls to sbrk, and the number of 
    // pages that have been requested
    NumSbrkCalls++; 
    NumPages += new_bytes/PAGESIZE;
    return new_p;
}

/* A function to change default operation of dynamic memory manager.
 * This function should be called before the first call to Mem_alloc.
 *
 * search_type: sets Search Policy to BEST_FIT (defults to FIRST_FIT)
 *
 * coalescing_state: sets Coalescing to TRUE (defaults to FALSE)
 */
void Mem_configure(int coalescing_state, int search_type)
{
    //assert(coalescing_state == TRUE || coalescing_state == FALSE);
    //assert(search_type == FIRST_FIT || search_type == BEST_FIT);
    Coalescing = coalescing_state;
    SearchPolicy = search_type;
}



/* deallocates the space pointed to by return_ptr; it does nothing if
 * return_ptr is NULL.  
 *
 * This function assumes that the rover pointer has already been 
 * initialized and points to some memory block in the free list.
 */
void Mem_free(void *Rptr){
    mem_chunk_t *return_ptr = ((mem_chunk_t *)Rptr) - 1;//type cast on usable data to save time
    int Flag;
    /*** two cases: if coalescing or not ***/
    if (Coalescing == FALSE){               //if not coalescing                           
        return_ptr->next = Rover->next;     //just stick the block wherever
        return_ptr->prev = Rover;
        Rover->next = return_ptr;                           
        return_ptr->next->prev = return_ptr;
        Rover = Rover->next;                          
    }else{
        while(1){
            /*if current address is less than returned block*/                                  
            if(((((long)Rover)>>4)&0x0FFFFFFFFFFFFFFF)<((((long)return_ptr)>>4)&0x0FFFFFFFFFFFFFFF)){
                if(Rover->next->num_units==0){  //if at the list end
                    Rover = Rover->next;
                    Flag = 1;                   //position found
                    break;
                }else{                          //if not at the end
                    Rover = Rover->next;        //move to next block
                } 
            }else{//if current address is greater than returned block
                /*if previous is greater than returned block and previous is not the dummy*/
                if((((((long)(Rover->prev))>>4)&0x0FFFFFFFFFFFFFFF)>((((long)return_ptr)>>4)&0x0FFFFFFFFFFFFFFF))&&(Rover->prev->num_units!=0)){
                    Rover=Rover->prev;  //move to previous block
                }else{                  //if at the end or in good position
                    Flag = 1;           //position found
                    break;
                }
            }
        }
        /*** insert between found blocks ***/
        return_ptr->next = Rover;
        return_ptr->prev = Rover->prev;
        Rover->prev->next = return_ptr;
        Rover->prev = return_ptr;
        Rover = Rover->prev->prev;
        /*** end insert ***/

        /*** attempt to coalesce ***/
        if(Rover+(Rover->num_units)!=Rover->next){  //if can't coalesce
            Rover = Rover->next;                    //move rover to next block
            Flag = 0;
            if(Rover+(Rover->num_units)==Rover->next){  //check block on otherside
                Flag = 1;                               //if valid, flag
            }
        }else{                                      //if valid, flag
            Flag = 1;
        }
        if(Flag==1){
            /*if you can coalesce, continue to do so until you can't*/
            mem_chunk_t *Temp;                                                          
            while(Rover+(Rover->num_units)==Rover->next){                       
                Rover->num_units = Rover->num_units + Rover->next->num_units;   
                Temp = Rover->next->next;                                       
                Rover->next->next = NULL;                                       
                Rover->next = Temp;                                             
                Temp->prev->prev = NULL;
                Temp->prev = Rover;
            }
        }
    }
}

/* returns a pointer to space for an object of size nbytes, or NULL if the
 * request cannot be satisfied.  The memory is uninitialized.
 *
 * This function assumes that there is a Rover pointer that points to
 * some item in the free list.  
 */
void *Mem_alloc(const int nbytes){
    /*** calculates number of units ***/
    int unitsize = sizeof(mem_chunk_t);
    int nunits;
    if(nbytes>unitsize){            //if more than one unit
        nunits = nbytes/unitsize;   //divide into units
        if(nbytes%unitsize!=0){     //if a remainder, add a unit
            nunits++;      
        }
    }else{                          //if one unit or less
        nunits = 1;
    }
    nunits++;                       //add one unit for the header
    /*** end unit calculation ***/

    /*** list search for valid block ***/
    mem_chunk_t *Initial;
    mem_chunk_t *return_ptr;
    int Flag = 0;
    Initial = Rover;
    if(SearchPolicy==FIRST_FIT){   
        /* first fit algorithm */
        while(1){
            if(Rover->num_units>=nunits){   //check if current block is right size
                Flag = 1;
                break;
            }else if(Rover->next!=Initial){ //check if haven't seen every element
                Rover = Rover->next;        //move to next element
            }else{                          //if didn't find an element
                Flag = 2;
                break;
            }
        }
    }else{
        /* best fit algorithm */
        mem_chunk_t *best = NULL;
        while(1){
            if(Rover->next!=Initial){                           //loop until list end
                if(Rover->num_units>=nunits){                   //if block is valid
                    if(best!=NULL){                             //if best exists already
                        if(best->num_units>Rover->num_units){   //if better than best
                            best = Rover;                       //reassign best
                        }
                    }else{                                      //if best doesn't exist                 
                        best = Rover;                           //assign best
                    }
                }                             
                Rover = Rover->next;                            //move to next block
            }else{                                              //if at the end
                if(Rover->num_units>=nunits){                   //if last block is valid
                    if(best!=NULL){                             //if best exists
                        if(best->num_units>Rover->num_units){   //if better than best
                            best = Rover;                       //reassign best
                        }
                        Flag = 1; 
                        break;                                  //found block
                    }else{                                      //if best doesn't exist                           
                        best = Rover;                           //assign best
                        Flag = 1;
                        break;                                  //found block
                    }
                }else{                                          //if last block not valid
                    if(best==NULL){                             //if best doesn't exist
                        Flag = 2;
                        break;                                  //no valid block in list
                    }else{                                      //if best does exist
                        Flag = 1;
                        break;                                  //found block
                    }
                }
            }
        }
        if(Flag==1){                                            //if a block was found      
            Rover = best;                                       //move to best block found
        }
    }
    /*** end list search algorithm ***/

    if(Flag==2){                                                //if no position found
        /*** calculates the number of pages ***/
        int ubytes = nunits * sizeof(mem_chunk_t);
        if(ubytes%PAGESIZE!=0){                                 //if not a multiple of page
            if(ubytes>PAGESIZE){                                //if larger than a page     
                ubytes = PAGESIZE * (ubytes/PAGESIZE + 1);      //find next multiple of a Page               
            }else{                                              //if smaller than a page
                ubytes = PAGESIZE;                              //round to one page
            }
        }
        /*** end page calculation ***/

        /*** memory addition ***/
        mem_chunk_t *NewBlock;
        NewBlock = morecore(ubytes);                        //request memory from OS  
        NewBlock->next = NULL;
        NewBlock->prev = NULL;  
        NewBlock->num_units = ubytes/sizeof(mem_chunk_t);   //assign header to new block
        Mem_free(NewBlock + 1);                             //add to free list
        /*** end memory addition ***/
    }
    Rover = Rover->prev;                                //move rover to previous for next step

    /*** carve memory block for user ***/
    return_ptr = Rover->next;                           //store return address
    if(Rover->next->num_units>nunits){                  //if carving is needed
        int carvedunits = 0;
        carvedunits = Rover->next->num_units - nunits;  //calculate left over memory
        Rover->next->num_units = nunits;                //change header to reflect new data
        Rover->next->prev = NULL;
        Rover->next = (Rover->next) + nunits;           //split block
        Rover->next->prev = Rover;
        Rover->next->num_units = carvedunits;           //assign new header to the left over block
        Rover->next->next = return_ptr->next;
        return_ptr->next->prev = Rover->next;
        return_ptr->next = NULL;
    }else{                                              //if carving not needed
        return_ptr->next->prev = Rover;                 //remove block
        Rover->next = Rover->next->next;
        return_ptr->next = NULL;
        return_ptr->prev = NULL;
    }
    return (return_ptr + 1);                            //return the address of the usable memory
    /*** end carving memory ***/
}

/* prints stats about the current free list
 *
 * -- number of items in the linked list including dummy item
 * -- min, max, and average size of each item (in bytes) but not considering
 *    dummy because its size is zero
 * -- total memory in free list (in bytes)
 * -- number of calls to sbrk and number of pages requested
 *
 * A message is printed if all the memory is in the free list
 */
void Mem_stats(void)
{
    int items_in_free_list = 0;
    int bytes_in_free_list = 0;
    double average_block_size = 0;
    int min_block_size = INT_MAX;
    int max_block_size = 0;

    mem_chunk_t *Initial;
    Initial=Rover;
    items_in_free_list++;
    bytes_in_free_list += Rover->num_units;
    Rover= Rover->next;

    while(Rover!=Initial){
        items_in_free_list++;                                       //add item for each move
        bytes_in_free_list += Rover->num_units;                     //sum all total bytes
        /*find max block*/
        if(Rover->num_units>max_block_size&&Rover->num_units!=0){   //if a value is greater than current max
            max_block_size = Rover->num_units;
        }
        /*find min block*/
        if(Rover->num_units<min_block_size&&Rover->num_units!=0){   //if a value is lower than current min
            min_block_size = Rover->num_units;
        }
        Rover = Rover->next;                                        //move to next block
    }
    if(Rover->num_units>max_block_size&&Rover->num_units!=0){   //last max check
        max_block_size = Rover->num_units;
    }
    max_block_size = max_block_size*sizeof(mem_chunk_t);
    if(Rover->num_units<min_block_size&&Rover->num_units!=0){   //last min check
        min_block_size = Rover->num_units;
    }
    min_block_size = min_block_size*sizeof(mem_chunk_t);
    bytes_in_free_list = bytes_in_free_list*sizeof(mem_chunk_t);            //calculate bytes via units
    if(items_in_free_list>1){                                               //divide by zero edge case
        average_block_size = (bytes_in_free_list/(items_in_free_list-1));   //calculate average
    }

    printf("  --- Free list stats ---\n");
    printf("\tCount of items : %d\n", items_in_free_list);
    printf("\tMemory in list : %d (bytes)\n", bytes_in_free_list);
    printf("\t           avg : %g (bytes)\n", average_block_size);
    printf("\t           min : %d (bytes)\n", min_block_size);
    printf("\t           max : %d (bytes)\n", max_block_size);
    printf("\tCalls to sbrk  : %d\n", NumSbrkCalls);
    printf("\tNumber of pages: %d\n", NumPages);
    if (bytes_in_free_list == NumPages * PAGESIZE) {
        printf("  all memory is in the heap -- no leaks are possible\n");
    }
    // if list is empty then just one item in the list.  It is the dummy
    // So min is zero by default.  Do not consider dummy in avg/min/max.
    //assert(min_block_size > 0 || items_in_free_list == 1);
}

/* print table of memory in free list 
 *
 * The print should include the dummy item in the list 
 *
 * A unit is the size of one mem_chunk_t structure
 */
void Mem_print(int nunits)
{
    // note position of Rover is not changed by this function
    mem_chunk_t *NOTROVER = Rover;
    mem_chunk_t *NOTINIT = NULL;
    if(nunits!=0){
        printf("\nDesired units = %d",nunits);
    }
    printf("\nCHAIN == ");
    NOTINIT = NOTROVER;
    NOTROVER = NOTROVER->next;
    while(NOTROVER!=NOTINIT){
        printf("%lX(%d), ",(long unsigned)NOTROVER,NOTROVER->num_units);
        NOTROVER = NOTROVER->next;
    }
    printf("%lX(%d)||\n\n",(long unsigned)NOTROVER,NOTROVER->num_units);
}

/* vi:set ts=8 sts=4 sw=4 et: */

