/* ids.c template
 * Gregory Pavlunenko
 * ECE 2230 Fall 2025
 * MP1
 *
 * Purpose: An Intrusion Detection System template for MP1 
 *
 * Assumptions: Assuming the caller is sending correct data
 *              very little checks are made to see if request
 *              indices exist
 *
 * Bugs: 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "ids.h"


/*
ids_construct creates a database of request size
*/
struct ids_database *ids_construct(int size)
{
    int i;
    struct ids_database *db_pointer;
    db_pointer = (struct ids_database *)malloc(sizeof(struct ids_database));
    db_pointer->db_size = size;
    db_pointer->db_initial_size = size;
    db_pointer->db_entries = 0;

    db_pointer->alert_ptr = (struct alert_t **)malloc(size * sizeof(struct alert_t));
    for (i=0;i<size;i++)
    {
        db_pointer->alert_ptr[i] = NULL;
    }

    return db_pointer;
}
/*
ids_destruct will delete the requested database
and free all the memory
*/
void ids_destruct(struct ids_database *list)
{
    int i;
    int k = list->db_entries;
    for(i=0; i<k; i++){
        free(list->alert_ptr[i]);
        list->alert_ptr[i] = NULL;
    }
    free(list->alert_ptr);
    list->alert_ptr = NULL;
    free(list);
    list = NULL;
}
/*
ids_add will create an entry into the requested
database
*/
int ids_add(struct ids_database *list, struct alert_t *rec_ptr)
{
    int dub = 0;
    /*place first item in first position*/
    if(list->db_entries==0){
        list->alert_ptr[0] = rec_ptr;
        list->db_entries++;
    }else{
        /*check to see if list is full*/
        int index,nulls,size,h,entries;
        size = list->db_size;
        entries = list->db_entries;
        nulls = size-entries;
        /*
        for(index=0;index<size;index++){
            if(list->alert_ptr[index]==NULL){
                nulls = 1;
            }
        }
            */
        /*double array size if full*/
        if(nulls==0){
            list->alert_ptr = (struct alert_t **)realloc(list->alert_ptr, 2 * (size) * sizeof(struct alert_t));
            for(index=size;index<list->db_size*2-list->db_size-1;index++){
                list->alert_ptr[index] = NULL;
            }
            list->db_size = list->db_size * 2;
            size = list->db_size;
            dub = 1;
            
        }
        /*finds new index position*/
        index = 0;
        while(index<size){
            if(index==list->db_entries||list->alert_ptr[index]->generator_id > rec_ptr->generator_id){
                h = index;
                index = size;
            }
            index++;
        }
        /*sorts the pointers into a new array and then changes 
        the alert to point to it instead while freeing the old array*/
        struct alert_t **new_ptr;
        new_ptr = (struct alert_t **)malloc(list->db_size * sizeof(struct alert_t));
        for(index=0;index<h;index++){
            new_ptr[index] = list->alert_ptr[index];
        }
        new_ptr[h] = rec_ptr;
        list->db_entries++;
        for(index=h+1;index<list->db_size;index++){
            new_ptr[index]  = list->alert_ptr[index-1];
        }
        free(list->alert_ptr);  
        list->alert_ptr = new_ptr;
        new_ptr = NULL;
    }
    return dub;
}
/*
ids_access will return the entry at the requested index
*/
struct alert_t *ids_access(struct ids_database *list, int index)
{
    int size;
    size = list->db_entries;
    struct alert_t *data_ptr;
    /*if requested data exist, send it*/
    if(index<size&&index>=0){
        data_ptr = list->alert_ptr[index];
    }else{
        data_ptr = NULL;
    }
    return data_ptr;
}
/*
ids_remove will remove an entry at the requested index
*/
struct alert_t *ids_remove(struct ids_database *list, int index)
{
    struct alert_t *data_ptr;
    int i,size;
    size = list->db_size;
    /*initial check for bounds and existance*/
    if(index<=size && index>=0 && list->alert_ptr[index]!=NULL){ 
        data_ptr = list->alert_ptr[index];
        /*cycle the pointers up one*/
        for(i=index;i<size;i++){
            if(index==size-1){
                list->alert_ptr[size-1] = NULL;
            }else{
                list->alert_ptr[i] = list->alert_ptr[i+1];
            }

        }
        list->db_entries--;
        list->alert_ptr[size] = NULL;
        int pointers = 0;
        pointers = list->db_entries;

        /*halves list size if low usage*/
        if(100*pointers/list->db_size<20 && list->db_size>list->db_initial_size){
            list->alert_ptr = (struct alert_t **)realloc(list->alert_ptr, list->db_size / 2 * sizeof(struct alert_t));
            list->db_size = list->db_size / 2;
        }
    }else{
        data_ptr = NULL;
    }
    return data_ptr;

}
/*
ids_empty will will tell you if the database is empty
*/
int ids_empty(struct ids_database *list)
{
    int empty = 1;
    if(list->db_entries>0){
        empty = 0;
    }
    return empty;
}
/*
ids_count will return number of entries
*/
int ids_count(struct ids_database *list)
{
    return list->db_entries;
}
/*
ids_size will return size of given datebase
*/
int ids_size(struct ids_database *list)
{
    return list->db_size;
}

/* Prompts user for alert record input starting with the source IP address.
 * The input is not checked for errors but will default to an acceptable value
 * if the input is incorrect or missing.
 *
 * The input to the function assumes that the structure has already been
 * created.  The contents of the structure are filled in.
 *
 * There is no output.
 *
 * Do not change the sequence of prompts as grading requires this exact
 * format
    return dub;
}

struct alert_t *ids_access(struct ids_database *list, int index)
{
    int size;
    size = list->db_size-1;
    struct alert_t *data_ptr;
    if(index<=size||list->alert_ptr[index]==NULL){
        data_ptr = list->alert_ptr[index];
    }else{
        data_ptr = NULL;
 */
void ids_record_fill(struct alert_t *rec)
{
    char line[MAXLINE];
    assert(rec != NULL);

    printf("Generator component:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->generator_id);
    printf("Signature:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->signature_id);
    printf("Revision:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->revision_id);
    printf("Dest IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->dest_ip_addr);
    printf("Source IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->src_ip_addr);
    printf("Destination port number:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->dest_port_num);
    printf("Source port number:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->src_port_num);
    printf("Time:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &rec->timestamp);
    printf("\n");
}

/* print the information for a particular alert record 
 *
 * Input is a pointer to a record, and no entries are changed.
 *
 * Do not change any of these lines and grading depends on this
 * format.
 */
void ids_print_rec(struct alert_t *rec)
{
    assert(rec != NULL);
    printf("[%d:%d:%d] (gen, sig, rev): ", rec->generator_id, rec->signature_id, 
            rec->revision_id);
    printf("Dest IP: %d, Src: %d, Dest port: %d,", rec->dest_ip_addr, 
            rec->src_ip_addr, rec->dest_port_num);
    printf(" Src: %d, Time: %d\n", rec->src_port_num, rec->timestamp); 
}


/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
