/* lab1.c template
 * Gregory Pavlunenko
 * gpavlun
 * ECE 2230 Fall 2025
 * MP1
 *
 *
 * Purpose: A simple if statement branch used to run the various 
 *          functions given in the ids.c file. used primarily for
 *          storing database information
 *
 * Assumptions: checks on user input are valid
 *
 * The program accepts one command line arguement that is the size of the list.
 *
 * Bugs:
 *
 * See the ECE 2230 programming guide
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "ids.h"

// this is a private function used for grading.  Do not change
void grading_db_size(struct ids_database *my_db_ptr, int old_size, int init_size);




int main(int argc, char **argv)
{
    struct alert_t *new_rec;
    char line[MAXLINE];
    char command[MAXLINE];
    char junk[MAXLINE];
    int num_items;
    int input_number;
    int list_size = -1;

    if (argc != 2) {
        printf("Usage: ./lab1 list_size\n");
        exit(1);
    }
    list_size = atoi(argv[1]);
    if (list_size < 1) {
        printf("lab1 has invalid list size: %d\n", list_size);
        exit(2);
    }
    printf("Welcome to lab1. Using list size: %d\n", list_size);
    printf("ALERT\nLISTGEN x, LISTIP x\nDELGEN x, DELIP x\nSCANGEN x\nPRINT\nQUIT\n");


    struct ids_database *mydb = ids_construct(list_size);


    while (fgets(line, MAXLINE, stdin) != NULL) {
        num_items = sscanf(line, "%s%d%s", command, &input_number, junk);
        if (num_items == 1 && strcmp(command, "QUIT") == 0) {
            ids_destruct(mydb);
            printf("cleanup\n");
            break;



        } else if (num_items == 1 && strcmp(command, "ALERT") == 0) {

            new_rec = (struct alert_t *)malloc(sizeof(struct alert_t));
            ids_record_fill(new_rec);
 
            /*add new record*/
            int add_return = ids_add(mydb, new_rec);
            

            if (add_return == 1) {
                printf("\nAdded: %d and doubled list size\n",new_rec->generator_id);
            } else if (add_return == 0) {
                printf("\nAdded: %d\n",new_rec->generator_id);
            } else {
                printf("\n\nError with ids_add return value\n");
                exit(1);
            }
            new_rec = NULL;
            



        } else if (num_items == 2 && strcmp(command, "LISTGEN") == 0) {
            
            int count, index, found;
            count = ids_count(mydb);
            found = 0;

            /*loop check each entry to see if they have matching ids and print them*/
            for(index=0;index<count;index++){
                new_rec = ids_access(mydb,index);
                if(new_rec!=NULL && new_rec->generator_id == input_number){
                    ids_print_rec(new_rec);
                    found++;
                }
            }
            /*print status*/
            if (found == 0) {
                printf("Did not find alert: %d\n", input_number);
            } else {
                printf("Found %d matching generator alerts %d\n", found, input_number);
            }
            new_rec = NULL;



        } else if (num_items == 2 && strcmp(command, "LISTIP") == 0) {
            int count, index, found;
            count = ids_count(mydb);
            found = 0;

            /*loop check each entry to see if they have matching destination and print them*/
            for(index=0;index<count;index++){
                new_rec = ids_access(mydb,index);
                if(new_rec!=NULL && new_rec->dest_ip_addr == input_number){
                    ids_print_rec(new_rec);
                    found++;
                }
            }
            /*print status*/
            if (found == 0) {
                printf("Did not find destination IP: %d\n", input_number);
            } else {
                printf("Found %d alerts matching IP %d\n", found, input_number);
            }
            new_rec = NULL;



        } else if (num_items == 2 && strcmp(command, "DELGEN") == 0) {
            struct alert_t *next_rec;
            int old_db_size = ids_size(mydb);
            int count, index, found;
            count = ids_count(mydb);
            found = 0;

            /*loop check each entry to see if they have id and deletes them*/
            for(index=0;index<count;index++){
                new_rec = ids_access(mydb,index);
                if(new_rec!=NULL && new_rec->generator_id == input_number){
                    next_rec = ids_remove(mydb,index);
                    free(next_rec);
                    found++;
                    index--;
                }
            }
            /*print status*/
            if (found == 0) {
                printf("Did not remove alert type: %d\n", input_number);
                assert(old_db_size == ids_size(mydb));
            } else {
                printf("Removed %d matching generator alerts %d\n", found, input_number);
                grading_db_size(mydb, old_db_size, list_size);
            }
            



        } else if (num_items == 2 && strcmp(command, "DELIP") == 0) {
            struct alert_t *next_rec;
            int old_db_size = ids_size(mydb);
            int count, index, found;
            count = ids_count(mydb);
            found = 0;

            /*loop check each entry to see if they have destination and deletes them*/
            for(index=0;index<count;index++){
                new_rec = ids_access(mydb,index);
                if(new_rec!=NULL && new_rec->dest_ip_addr == input_number){
                    next_rec = ids_remove(mydb,index);
                    free(next_rec);
                    found++;
                    index--;
                }
            }
            /*print status*/
            if (found == 0) {
                printf("Did not remove any alert with IP: %d\n", input_number);
            } else {
                printf("Removed %d alerts matching IP %d\n", found, input_number);
                grading_db_size(mydb, old_db_size, list_size);
            }

            

        } else if (num_items == 2 && strcmp(command, "SCANGEN") == 0) {
            new_rec = ids_access(mydb,0);
            int groups;
            groups = 0;

            /*checks to see if there is anything in the array*/
            if(new_rec != NULL){
                struct alert_t *next_rec;
                int *unique_values;
                int size = 1;
                int records, index, jindex, kindex, pass, position, count;
                
                /*creates a new array to store all unique codes*/
                unique_values = (int *)malloc(size * sizeof(int));
                
                new_rec = NULL;
                next_rec = NULL;
                records = ids_count(mydb);
                position = 0;
                groups = 0;

                /*check every id in the array*/
                for(index=0; index<records; index++){
                    new_rec = ids_access(mydb,index);
                    pass = 0;
                    
                    /*special case for first value*/
                    if(index==0){
                        unique_values[0] = new_rec->generator_id;
                        position++;
                    }else{
                        /*check against every unique value*/
                        for(jindex=0; jindex<size; jindex++){
                            if(unique_values[jindex]==new_rec->generator_id){
                                pass = 1;
                                count = 0;
                            }
                        }
                    }

                    /*if the id has not been seen yet*/
                    if(pass==0){
                        /*creates a new spot in the unique value array*/
                        if(index!=0){
                            unique_values = (int *)realloc(unique_values,(size+1)*sizeof(int));
                            size++;
                            unique_values[position] = new_rec->generator_id;
                            position++;
                        }
                        count = 0;
                        /*counts how many times the id appears*/
                        for(kindex=0; kindex<records; kindex++){
                            next_rec = ids_access(mydb, kindex);
                            if(new_rec->generator_id == next_rec->generator_id){
                                count++;
                            }
                        }
                    }
                    /*if it appears above the threshold, prints*/
                    if(count>=input_number){
                        printf("A set with generator %d has %d alerts\n", new_rec->generator_id, count);
                        groups++;
                    }
                }
                /*removes the unique value array*/
                free(unique_values);
                unique_values = NULL;
            }
            /*prints how many alert types were above the threshold*/
            if (groups > 0) {
                printf("Found %d sets with at least %d matches\n", groups, input_number);
            } else {
                printf("No records with >= %d matches\n", input_number);
            }
            
            
        
        } else if (num_items == 1 && strcmp(command, "PRINT") == 0) {
            int num_in_list = ids_count(mydb);
            int array_size = ids_size(mydb);
            if (num_in_list == 0) {
                printf("List empty. DB size is %d\n", array_size);
            } else {
                printf("List has %d records. DB size is %d\n", num_in_list, array_size);
                int i;
                for (i = 0; i < num_in_list; i++) {

                    new_rec = ids_access(mydb, i);
                    if(new_rec!=NULL){
                        printf("%d: ", i+1);
                        ids_print_rec(new_rec);
                    }

                }
            }
            new_rec = NULL;
        } else {
            printf("# %s", line);
        }
    }
    exit(0);
}

/* this is a function for grading.  It checks if the size of the database was
 * correctly reduced after items were deleted.
 *
 * DO NOT CHANGE THIS FUNCTION.   It is used during grading to verify resizing
 * of the list is working
 */
void grading_db_size(struct ids_database *my_db_ptr, int old_size, int init_size) 
{
    int alert_count = ids_count(my_db_ptr);
    int new_db_size = ids_size(my_db_ptr);
    if (new_db_size < old_size) {
        printf("    Reduced size of database to %d\n", new_db_size);
        if (new_db_size < init_size) {
            printf("   ERROR, the size of database reduced too much.  Must be at least %d\n", init_size);
            assert(new_db_size >= init_size);
        }
    } else {
        assert(new_db_size == old_size);
        if (alert_count < new_db_size/5.0 && new_db_size >= 2*init_size) {
            printf("   ERROR, did not reduce size of database.  Count=%d, db size = %d\n", alert_count, new_db_size);
            assert(alert_count >= new_db_size/5.0 || new_db_size < 2*init_size);
        }
    }
}

/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
