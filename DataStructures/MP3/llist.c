/* llist.c                 
 * Gregory Pavlunenko
 * gpavlun
 * gpavlun 
 * ECE 2230 Fall 2025
 * MP3
 *
 * Propose: functions for my linked list
 *
 * Assumptions: I am assuming that I can do this whole thing in 2 days 
 *
 * Bugs: couple of roaches
 *
 */
#define _GNU_SOURCE 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "llist.h"        // defines public functions for list ADT

// definitions for private constants used in llist.c only

#define LLIST_SORTED    989898
#define LLIST_UNSORTED -898989

// prototypes for private functions used in llist.c only 

void llist_debug_validate(llist_t *L);

/* ----- below are the functions  ----- */

/*---------------------------------------------------*/
/*------------- NEW FUNCTIONS IN lAB 3 --------------*/
/*---------------------------------------------------*/



/* Qsort Functions given by Dr. Russel, I did not try to figure out how they work
 *
 */
int qsort_compare(const void *p_a, const void *p_b, void * lptr)
{
    llist_t *list_ptr = (llist_t *) lptr;
    return list_ptr->compare_fun (*(data_t **) p_b, *(data_t **) p_a);
}

void qsort_llist(llist_t *list_ptr) 
{
    int i, Asize = llist_entries(list_ptr);
    assert(list_ptr->compare_fun != NULL);
    data_t ** QsortA = (data_t **) malloc(Asize*sizeof(data_t *));

    for (i = 0; i < Asize; i++) {
        QsortA[i] = llist_remove(list_ptr, LLPOSITION_FRONT);
    }

    qsort_r(QsortA, Asize, sizeof(data_t *), qsort_compare, list_ptr);

    for (i = 0; i < Asize; i++) {
        llist_insert(list_ptr, QsortA[i], LLPOSITION_BACK);
    }
    free(QsortA);
}



/* Obtains a pointer to an element stored in the specified list, at the
 * given functions discretion
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from llist_construct.
 *
 * m: initial postition
 * 
 * n: ending position
 *
 * return value: pointer to element accessed within the specified list
 */
llist_elem_t *FindMax(llist_t *list_ptr, llist_elem_t *m, llist_elem_t *n)
{
    llist_elem_t *fido = m;     
    llist_elem_t *ret = m;     
    /*keeps moving to the next value until it finds the largest one*/
    do {
        fido=fido->ll_next;                      
        if (list_ptr->compare_fun(fido->data_ptr,ret->data_ptr)==1) {         
            ret = fido;              
        }
    } while (fido != n);           

    return ret;                       
}  



/* Sorts two values in a list and calls itself again recursively
 * until it has sorted everything
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from llist_construct.
 *
 * m: current position
 * 
 * n: last position in the list
 *
 * output: sorted list
 */
void SelectionSort(llist_t *list_ptr, llist_elem_t *m, llist_elem_t *n){
    llist_elem_t *MaxPosition;   
    llist_elem_t *temp;                    
    if (m!=list_ptr->ll_back) {               
        MaxPosition = FindMax(list_ptr,m,n);
        if(MaxPosition!=m){

            temp = (llist_elem_t *)calloc(1, sizeof(llist_elem_t));
            if(list_ptr->ll_front==m){
                list_ptr->ll_front = temp;
            }else{
                m->ll_prev->ll_next = MaxPosition;
            }
            temp->ll_next = m->ll_next;
            temp->ll_prev = m->ll_prev;
            


            if(list_ptr->ll_back==MaxPosition){
                list_ptr->ll_back = m;
            }else{
                MaxPosition->ll_next->ll_prev = m;
            }
            m->ll_next = MaxPosition->ll_next;
            if(MaxPosition->ll_prev==m){
                m->ll_prev = MaxPosition;
            }else{
                m->ll_prev = MaxPosition->ll_prev;
                MaxPosition->ll_prev->ll_next = m;
            }
            


            if(list_ptr->ll_front==temp){
                list_ptr->ll_front = MaxPosition;
            }
            if(temp->ll_next==MaxPosition){
                MaxPosition->ll_next = m;
            }else{
                MaxPosition->ll_next = temp->ll_next;
                temp->ll_next->ll_prev = MaxPosition;
            }
            MaxPosition->ll_prev = temp->ll_prev;
            free(temp);
        }

        SelectionSort(list_ptr, MaxPosition->ll_next, list_ptr->ll_back);
    }
}



/* Sorts a list iteratively in the same manner as selection sort
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from llist_construct.
 *
 * output: sorted list
 */
void IterativeSelectionSort(llist_t *list_ptr)
{
    llist_elem_t *fido;
    llist_elem_t *MaxPosition;   
    llist_elem_t *temp;
    llist_elem_t *m = list_ptr->ll_front;


    while (m!=list_ptr->ll_back) {

        fido = m; 
        MaxPosition = m;

        do {
            
            fido = fido->ll_next;
            if ( list_ptr->compare_fun(fido->data_ptr,MaxPosition->data_ptr)==1 ){
                MaxPosition = fido;
            } 
        } while (fido != list_ptr->ll_back);



        if(MaxPosition!=m){
            temp = (llist_elem_t *)calloc(1, sizeof(llist_elem_t));
            if(list_ptr->ll_front==m){
                list_ptr->ll_front = temp;
            }else{
                m->ll_prev->ll_next = MaxPosition;
            }
            temp->ll_next = m->ll_next;
            temp->ll_prev = m->ll_prev;
            


            if(list_ptr->ll_back==MaxPosition){
                list_ptr->ll_back = m;
            }else{
                MaxPosition->ll_next->ll_prev = m;
            }
            m->ll_next = MaxPosition->ll_next;
            if(MaxPosition->ll_prev==m){
                m->ll_prev = MaxPosition;
            }else{
                m->ll_prev = MaxPosition->ll_prev;
                MaxPosition->ll_prev->ll_next = m;
            }



            if(list_ptr->ll_front==temp){
                list_ptr->ll_front = MaxPosition;
            }
            if(temp->ll_next==MaxPosition){
                MaxPosition->ll_next = m;
            }else{
                MaxPosition->ll_next = temp->ll_next;
                temp->ll_next->ll_prev = MaxPosition;
            }
            MaxPosition->ll_prev = temp->ll_prev;
            free(temp);
        }
        m = MaxPosition->ll_next;
    }
}



/* Takes two lists and combines them together in order
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from llist_construct.
 * left: one input list to be combined
 * 
 * reft: other input list to be combined
 * 
 * output: sorted list
 */
void Unsplit(llist_t *list_ptr,llist_t *left, llist_t *reft){
    int i,j;
    while(left->ll_front!=NULL&&reft->ll_front!=NULL){
        if(list_ptr->compare_fun(left->ll_front->data_ptr,reft->ll_front->data_ptr)==1){
            llist_insert(list_ptr, llist_remove(left,0),LLPOSITION_BACK);
        }else{
            llist_insert(list_ptr, llist_remove(reft,0),LLPOSITION_BACK);
        }
    }
    if(left->ll_front!=NULL){
        j = left->ll_entry_count;
        for(i=0;i<j;i++){
            llist_insert(list_ptr, llist_remove(left,0),LLPOSITION_BACK);
        }
    }
    if(reft->ll_front!=NULL){
        j = reft->ll_entry_count;
        for(i=0;i<j;i++){
            llist_insert(list_ptr, llist_remove(reft,0),LLPOSITION_BACK);
        }
    }
}



/* Merged Sort sorting algorithm
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from llist_construct.
 * 
 * output: sorted list
 */
void MergeSort(llist_t *list_ptr){

    if(list_ptr->ll_front->ll_next!=NULL) {
        int i = 0;
        llist_elem_t *fido = list_ptr->ll_front;
        while(fido!=NULL){
            fido = fido->ll_next;
            i++;
        }
        llist_t *left = (llist_t *)calloc(1,sizeof(llist_t));
        llist_t *reft = (llist_t *)calloc(1,sizeof(llist_t));;

        left->ll_front = list_ptr->ll_front;
        fido = left->ll_front;

        int j = 0;
        for(j=0;j<i/2;j++){
            fido = fido->ll_next;
        }
        left->ll_entry_count = i/2;
        if(i%2==1){
            reft->ll_entry_count = i/2+1;
        }else{
            reft->ll_entry_count = i/2;
        }
        reft->ll_front = fido;
        fido->ll_prev->ll_next = NULL;
        left->ll_back = fido->ll_prev;
        fido->ll_prev = NULL;
        reft->ll_back = list_ptr->ll_back;
        left->compare_fun = list_ptr->compare_fun;
        reft->compare_fun = list_ptr->compare_fun;

        list_ptr->ll_front = NULL;
        list_ptr->ll_back = NULL;
        list_ptr->ll_entry_count = 0;
        list_ptr->ll_sorted_state = LLIST_SORTED;
        MergeSort(left);
        MergeSort(reft);
        Unsplit(list_ptr, left, reft);
        free(left);
        free(reft);
    }
}



/* llist_sort is functionally just a switch statement for the various sorting algorithms
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from llist_construct.
 *
 * sort_type: value used to identify how the list should be sorted
 * 
 * fcomp: function used to compare values for sorting
 *
 */
void llist_sort(llist_t *list_ptr, int sort_type, int (*fcomp)(const data_t *, const data_t *)){


    if(sort_type==1){

        /*** Insertion Sort ***/

        list_ptr->compare_fun = fcomp;
        list_ptr->ll_sorted_state = LLIST_SORTED;

        llist_t *new_list = (llist_t *)calloc(1, sizeof(llist_t));
        int i=0,k=0;
        new_list->ll_sorted_state = LLIST_SORTED;
        new_list->compare_fun = list_ptr->compare_fun;
        k = list_ptr->ll_entry_count;
        
        if(k>0){
            
            for(i=0;i<k;i++){    
                llist_insert_sorted(new_list, llist_remove(list_ptr,0));
            }
            list_ptr->ll_entry_count = k;
            list_ptr->ll_front = new_list->ll_front;
            list_ptr->ll_back = new_list->ll_back;
        }
        free(new_list);

    }else if(sort_type==2){

        /*** Recursive Selection Sort ***/
        list_ptr->compare_fun = fcomp;
        SelectionSort(list_ptr,list_ptr->ll_front,list_ptr->ll_back);


    }else if(sort_type==3){
        /*** Iterative Selectin Sort ***/
        list_ptr->compare_fun = fcomp;
        IterativeSelectionSort(list_ptr);

    }else if(sort_type==4){
        /*** Merge Sort ***/
        list_ptr->compare_fun = fcomp;
        MergeSort(list_ptr);


    }else if(sort_type==5){
        /*** Quick Sort ***/
        list_ptr->compare_fun = fcomp;
        qsort_llist(list_ptr);

    }
    list_ptr->ll_sorted_state = LLIST_SORTED;
    llist_debug_validate(list_ptr);
}





/*---------------------------------------------------*/
/*---------------- END NEW FUNCTIONS ----------------*/
/*---------------------------------------------------*/



/* Obtains a pointer to an element stored in the specified list, at the
 * specified list position
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from llist_construct.
 *
 * pos_index: position of the element to be accessed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LLPOSITION_FRONT and LLPOSITION_BACK
 *
 * return value: pointer to element accessed within the specified list.  A
 * value NULL is returned if the pos_index does not correspond to an element in
 * the list.
 */
data_t * llist_access(llist_t *list_ptr, int pos_index)
{
    llist_elem_t *fido = NULL;
 
    // debugging function to verify that the structure of the list is valid
    //llist_debug_validate(list_ptr);

    /* handle special cases.
     *   1.  The list is empty
     *   2.  Asking for the head 
     *   3.  Asking for the tail
     *   4.  specifying a position that is out of range.  This is not defined
     *       to be an error in this function, but instead it is assumed the 
     *       calling function correctly specifies the position index
     */
    if (list_ptr->ll_entry_count == 0) {
        return NULL;  // list is empty
    }
    else if (pos_index == LLPOSITION_FRONT || pos_index == 0) {
        return list_ptr->ll_front->data_ptr;
    }
    else if (pos_index == LLPOSITION_BACK || pos_index == list_ptr->ll_entry_count - 1) {
        return list_ptr->ll_back->data_ptr;
    }
    else if (pos_index < 0 || pos_index >= list_ptr->ll_entry_count){
        return NULL;   // does not correspond to position in list
    }
        
    // loop through the list until find correct position index
    fido = list_ptr->ll_front;
    for(int i = 0;i<pos_index;i++){
        fido=fido->ll_next;
    }
 
    // already verified that pos_index should be valid so rover better not be null
    assert(fido != NULL);
    assert(fido->data_ptr != NULL);
    return fido->data_ptr;
}

/* Allocates a new, empty list 
 *
 * If the comparison function is NULL, then the list is unsorted.
 *
 * Otherwise, the list is initially assumed to be sorted.  Note that if 
 * list_insert is used the list is changed to unsorted.  
 *
 * The field sorted can only take values LLIST_SORTED or LLIST_UNSORTED
 *
 * Use llist_destruct to remove and deallocate all elements on a list 
 * and the header block.
 *
 * (This function is written and no changes needed. It provides an example
 *  of how save the comparison function pointer.  See other examples in this
 *  file for how to use compare_fun.)
 */
llist_t * llist_construct(int (*fcomp)(const data_t *, const data_t *))
{
    llist_t *new_list;
    new_list = (llist_t *) malloc(sizeof(llist_t));
    new_list->ll_front = NULL;
    new_list->ll_back = NULL;
    new_list->ll_entry_count = 0;
    new_list->compare_fun = fcomp;
    if (fcomp == NULL)
        new_list->ll_sorted_state = LLIST_UNSORTED;
    else
        new_list->ll_sorted_state = LLIST_SORTED;

    //llist_debug_validate(new_list);
    return new_list;
}




/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: element against which other elements in the list are compared.
 * 
 * fcomp: function to test if elem_ptr is a match to an item in the list.
 *        Returns 0 if they match and any value not equal to 0 if they do not match.
 *
 * NOTICE: pos_index is returned and is not an input value!
 *
 * The function returns a pointer to the matching element with lowest index if
 * a match if found.  If a match is not found the return value is NULL.
 *
 * The function also returns the integer position of matching element with the
 *           lowest index.  If a matching element is not found, the position
 *           index that is returned should be -1. 
 *
 * pos_index: used as a return value for the position index of matching element
 *
 */
data_t *llist_elem_find(llist_t *list_ptr, data_t *elem_ptr, int *pos_index,
        int (*fcomp)(const data_t *, const data_t *))
{
    //llist_debug_validate(list_ptr);
    llist_elem_t *fido;
    *pos_index = 0;
    fido = list_ptr->ll_front;

    for(int i=0;i<list_ptr->ll_entry_count;i++){

        if(fcomp(fido->data_ptr,elem_ptr)!=0){

            (*pos_index)++;
            fido = fido->ll_next;

        }else{
            return fido->data_ptr;
        }
    }
    *pos_index = -1;
    return NULL;
}






/* Deallocates the contents of the specified list, releasing associated memory
 * resources for other purposes.
 */
void llist_destruct(llist_t *list_ptr)
{
    // the first line must validate the list 
    //llist_debug_validate(list_ptr);

    // Your code starts here

    llist_elem_t *fido, *odif;
    fido = list_ptr->ll_back;
    odif = NULL;
    while(fido!=NULL){
        free(fido->data_ptr);
        odif = fido;
        fido = fido->ll_prev;
        free(odif);
    }
    free(list_ptr);
}

/* Inserts the specified data element into the specified list at the specified
 * position.
 *
 * llist_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * pos_index: numeric position index of the element to be inserted into the 
 *            list.  Index starts at 0 at head of the list, and incremented by 
 *            one until the tail is reached.  The index can also be equal
 *            to LLPOSITION_FRONT or LLPOSITION_BACK (these are special negative 
 *            values use to provide a short cut for adding to the head
 *            or tail of the list).
 *
 * If pos_index is greater than the number of elements currently in the list, 
 * the element is simply appended to the end of the list (no additional elements
 * are inserted).
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the llist_ptr->ll_sorted_state must be equal 
 * to LLIST_UNSORTED.
 */
void llist_insert(llist_t *list_ptr, data_t *elem_ptr, int pos_index)
{
    assert(list_ptr != NULL);
    assert(pos_index == LLPOSITION_FRONT || pos_index == LLPOSITION_BACK || pos_index >= 0);
    // note you MUST handle the case that pos_index is LLPOSITION_FRONT or BACK




    // insert your code here
    llist_elem_t *element;
    element = (llist_elem_t *)calloc(1,sizeof(llist_elem_t));
    element->data_ptr = elem_ptr;

    if(list_ptr->ll_entry_count==0){
        list_ptr->ll_front = element;
        list_ptr->ll_back = element;
        element->ll_next = NULL;
        element->ll_prev = NULL; 
    }else{
        if(pos_index==LLPOSITION_FRONT || pos_index==0){
            element->ll_next = list_ptr->ll_front;
            list_ptr->ll_front->ll_prev = element;
            list_ptr->ll_front = element;
            element->ll_prev = NULL;
        }else if(pos_index==LLPOSITION_BACK || pos_index>=list_ptr->ll_entry_count){
            element->ll_prev = list_ptr->ll_back;
            list_ptr->ll_back->ll_next = element;
            list_ptr->ll_back = element;
            element->ll_next = NULL;
        }else{
            llist_elem_t *fido,*odif;
            fido = list_ptr->ll_front;
            odif = NULL;
            for(int i; i<pos_index;i++){
                odif = fido;
                fido = fido->ll_next;
            }
            odif->ll_next = element;
            element->ll_next = fido;
            fido->ll_prev = element;
            element->ll_prev = odif;
        }
    }
    list_ptr->ll_entry_count++;




    // the last three lines of this function must be the following 
    if (list_ptr->ll_sorted_state == LLIST_SORTED) 
        list_ptr->ll_sorted_state = LLIST_UNSORTED;
    //llist_debug_validate(list_ptr);
}

/* Inserts the element into the specified sorted list at the proper position,
 * as defined by the compare_fun function pointer found in the list header:
 *     list_ptr->compare_fun(A, B)
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * If you use llist_insert_sorted, the list preserves its sorted nature.
 *
 * If you use llist_insert, the list will be considered to be unsorted, even
 * if the element has been inserted in the correct position.
 *
 * If the list is not sorted and you call llist_insert_sorted, this subroutine
 * should generate a system error and the program should immediately stop.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type data_t.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the list head than B
 *   -1: B should be closer to the list head than A
 *    0: A and B are equal in rank
 *
 * Note: if the element to be inserted is equal in rank to an element already
 *       in the list, the newly inserted element will be placed after all the 
 *       elements of equal rank that are already in the list.
 */
void llist_insert_sorted(llist_t *list_ptr, data_t *elem_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->ll_sorted_state == LLIST_SORTED);

    // insert your code here
    int change = 0;
    llist_elem_t *new_element, *fido, *odif;
    new_element = (llist_elem_t *)calloc(1,sizeof(llist_elem_t));
    new_element->data_ptr = elem_ptr;
    new_element->ll_next = NULL;
    new_element->ll_prev = NULL;
    fido = list_ptr->ll_front;
    odif = NULL;

    if(list_ptr->ll_front==NULL){
        list_ptr->ll_front = new_element;
        list_ptr->ll_back = new_element;
    }else{

        while(change!=1&&fido!=NULL){
            change = list_ptr->compare_fun(new_element->data_ptr, fido->data_ptr);
            if(change!=1){
                odif = fido;
                fido = fido->ll_next;

            }
        }
        if(fido==NULL){
            odif->ll_next = new_element;
            new_element->ll_prev = odif;
            list_ptr->ll_back = new_element;
            new_element->ll_next = NULL;
        }else if(fido==list_ptr->ll_front){
            list_ptr->ll_front = new_element;
            new_element->ll_prev = NULL;
            new_element->ll_next = fido;
            fido->ll_prev = new_element;
        }else{
            odif->ll_next = new_element;
            new_element->ll_prev = odif;
            fido->ll_prev = new_element;
            new_element->ll_next = fido;
        }
    }
    list_ptr->ll_entry_count++;




    // the last line checks if the new list is correct 
    //llist_debug_validate(list_ptr);
}

/* Removes an element from the specified list, at the specified list position,
 * and returns a pointer to the element.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * pos_index: position of the element to be removed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LLPOSITION_FRONT and LLPOSITION_BACK
 *
 * Attempting to remove an element at a position index that is not contained in
 * the list will result in no element being removed, and a NULL pointer will be
 * returned.
 */
data_t * llist_remove(llist_t *list_ptr, int pos_index)
{
    assert(list_ptr != NULL);
    assert(pos_index == LLPOSITION_FRONT || pos_index == LLPOSITION_BACK || pos_index >= 0);
    // note you MUST handle the case that pos_index is LLPOSITION_FRONT or BACK
 

    // insert your code here 
    if(pos_index == LLPOSITION_BACK){
        pos_index = list_ptr->ll_entry_count-1;
    }else if(pos_index == LLPOSITION_FRONT){
        pos_index = 0;
    }
    llist_elem_t *fido,*odif;
    data_t *ret;
    ret = NULL;

    if(pos_index>=0 && pos_index<list_ptr->ll_entry_count){
        fido = list_ptr->ll_front;
        if(list_ptr->ll_entry_count>1){
            if(pos_index!=0 && pos_index!=(list_ptr->ll_entry_count-1)){
                for(int i = 0; i<pos_index; i++){
                    odif = fido;
                    fido=fido->ll_next;
                }
                odif->ll_next = fido->ll_next;
                fido->ll_next->ll_prev = odif;
                fido->ll_next = NULL;
                fido->ll_prev = NULL;
                ret = fido->data_ptr;
            }else if(pos_index==0){
                list_ptr->ll_front = fido->ll_next;
                fido->ll_next->ll_prev = NULL;
                fido->ll_next = NULL;
                fido->ll_prev = NULL;
                ret = fido->data_ptr;
            }else if(pos_index==(list_ptr->ll_entry_count-1)){
                fido = list_ptr->ll_back;
                odif = fido->ll_prev;
                list_ptr->ll_back = odif;
                fido->ll_prev = NULL;
                odif->ll_next = NULL;
                ret = fido->data_ptr;
            }

        }else{
            ret = fido->data_ptr;
            list_ptr->ll_front = NULL;
            list_ptr->ll_back = NULL;
        }
        list_ptr->ll_entry_count--;

    }
    if(fido!=NULL){
        free(fido);
    }
    return ret;

    
    


    // the last line should verify the list is valid after the remove
    //llist_debug_validate(list_ptr);
}

/* Obtains the length of the specified list, that is, the number of elements
 * that the list contains.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * Returns an integer equal to the number of elements stored in the list.  An
 * empty list has a size of zero.
 *
 * (This function is already written, so no changes necessary.)
 */
int llist_entries(llist_t *list_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->ll_entry_count >= 0);
    return list_ptr->ll_entry_count;
}


/* This function verifies that the pointers for the two-way linked list are
 * valid, and that the list size matches the number of items in the list.
 *
 * If the linked list is sorted it also checks that the elements in the list
 * appear in the proper order.
 *
 * The function produces no output if the two-way linked list is correct.  It
 * causes the program to terminate and print a line beginning with "Assertion
 * failed:" if an error is detected.
 *
 * The checks are not exhaustive, so an error may still exist in the
 * list even if these checks pass.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void llist_debug_validate(llist_t *L)
{
    llist_elem_t *N;
    int count = 0;
    assert(L != NULL);
    if (L->ll_front == NULL)
        assert(L->ll_back == NULL && L->ll_entry_count == 0);
    if (L->ll_back == NULL)
        assert(L->ll_front == NULL && L->ll_entry_count == 0);
    if (L->ll_entry_count == 0)
        assert(L->ll_front == NULL && L->ll_back == NULL);
    if (L->ll_entry_count == 1) {
        assert(L->ll_front == L->ll_back && L->ll_front != NULL);
        assert(L->ll_front->ll_next == NULL && L->ll_front->ll_prev == NULL);
        assert(L->ll_front->data_ptr != NULL);
    }
    if (L->ll_front == L->ll_back && L->ll_front != NULL)
        assert(L->ll_entry_count == 1);
    assert(L->ll_sorted_state == LLIST_SORTED || L->ll_sorted_state == LLIST_UNSORTED);
    if (L->ll_entry_count > 1) {
        assert(L->ll_front != L->ll_back && L->ll_front != NULL && L->ll_back != NULL);
        N = L->ll_front;
        assert(N->ll_prev == NULL);
        while (N != NULL) {
            assert(N->data_ptr != NULL);
            if (N->ll_next != NULL) assert(N->ll_next->ll_prev == N);
            else assert(N == L->ll_back);
            count++;
            N = N->ll_next;
        }
        assert(count == L->ll_entry_count);
    }
    if (L->ll_sorted_state == LLIST_SORTED && L->ll_front != NULL) {
        N = L->ll_front;
        while (N->ll_next != NULL) {
            assert(L->compare_fun(N->data_ptr, N->ll_next->data_ptr) != -1);   // A <= B
            N = N->ll_next;
        }
    }
}
/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
