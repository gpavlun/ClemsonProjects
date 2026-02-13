#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "table.h"
#include "hashes.h"

#define EMPTY 0
#define DELETED 1
#define OCCUPIED 2
#define NKEY 3

#define LINEAR 0
#define DOUBLE 1
#define CHAIN 2
/*  The empty table is created.  The table must be dynamically allocated and
 *  have a total size of table_size.  The maximum number of (K, I) entries
 *  that can be stored in the table is table_size-1.  For open addressing, 
 *  the table is filled with a special empty key distinct from all other 
 *  nonempty keys (e.g., NULL).  
 *
 *  the probe_type must be one of {LINEAR, DOUBLE, CHAIN}
 *
 *  Do not "correct" the table_size or probe decrement if there is a chance
 *  that the combinaion of table size or probe decrement will not cover
 *  all entries in the table.  Instead we will experiment to determine under
 *  what conditions an incorrect choice of table size and probe decrement
 *  results in poor performance.
 *
 *  Malloc one table for either open addressing or separate 
 *  chaining.  But only allocate one of them depending on the probe_type
 */
table_t *table_construct(int table_size, int probe_type){
    table_t *TableHeader;
    TableHeader = (table_t *)malloc(sizeof(table_t));
    TableHeader->num_keys = 0;
    TableHeader->probe_type = probe_type;
    TableHeader->recent_probes = 0;
    TableHeader->table_size = table_size;
    int i;
    if(probe_type==CHAIN){
        /*creates an array of pointers to elements*/
        elem_t **TableElement;
        TableElement = (elem_t **)malloc(sizeof(elem_t *) * table_size);
        TableHeader->table_elements = (void *)TableElement;
        elem_t *ListElement;

        for(i=0;i<table_size;i++){
            ListElement = (elem_t *)malloc(sizeof(elem_t));
            *(TableElement + i) = ListElement;
            ListElement->data = NULL;
            ListElement->status = EMPTY;
            ListElement->next = NULL;
        }
    }else{
        /*creates an array of elements*/
        elem_t *TableElement;
        TableElement = (elem_t *)malloc(sizeof(elem_t) * table_size);
        TableHeader->table_elements = (void *)TableElement;
                
        for(i=0;i<table_size;i++){
            (TableElement + i)->data = NULL;
            (TableElement + i)->status = EMPTY;
            (TableElement + i)->next = NULL;
        }
    }
    return TableHeader;
}



/* Sequentially remove each table entry (K, I) and insert into a new
 * empty table with size new_table_size.  Free the memory for the old table.
 * Update the header, T, to point to the new table with its
 * new size.  The probe type should remain the same.
 *
 * Do not rehash the table during an insert or delete function call.  Instead
 * use drivers to verify under what conditions rehashing is required, and
 * call the rehash function in the driver to show how the performance
 * can be improved.
 */
void table_rehash(table_t *TableHeader, int new_table_size){
    table_t *NewTable = table_construct(new_table_size,TableHeader->probe_type);
    int i;
    //printf("%lX\n%lX\n",NewTable,TableHeader);

    int table_size = TableHeader->table_size;
    if(TableHeader->probe_type!=CHAIN){
        elem_t *TableElement = (elem_t *)(TableHeader->table_elements);
        for(i=0;i<table_size;i++){
            if((TableElement + i)->status==OCCUPIED){
                table_insert(NewTable,(TableElement + i)->hashkey,(TableElement + i)->data);
            }
        }
        free(TableElement);
    }else{
        elem_t **TableElement = (elem_t **)(TableHeader->table_elements);
        elem_t *ListElement = *TableElement;
        for(i=0;i<table_size;i++){
            ListElement = *(TableElement + i);
            while(ListElement!=NULL){
                if(ListElement->status==OCCUPIED){
                    table_insert(NewTable,ListElement->hashkey,ListElement->data);
                }
                ListElement = ListElement->next;
            }
        }
        elem_t *rover;
        elem_t *prev;
        for(i=0;i<table_size;i++){
            rover = *(TableElement + i);
            while(rover!=NULL){
                prev = rover;
                rover = rover->next;
                free(prev);
            }
        }
        free(TableElement);
        
    }
    TableHeader->num_keys = NewTable->num_keys;
    TableHeader->probe_type = NewTable->probe_type;
    TableHeader->recent_probes = NewTable->recent_probes;
    TableHeader->table_elements = NewTable->table_elements;
    TableHeader->table_size = NewTable->table_size;
    free(NewTable);
    //printf("%lX\n%lX\n",NewTable,TableHeader);
}



/* Returns the number of entries in the table.  Store this value
 * in the table header because this function is called frequently
 */
int table_entries(table_t *TableHeader){
    return TableHeader->num_keys;
}



/* returns 1 if table is full and 0 if not full. 
 * For separate chaining the table is never full
 */
int table_full(table_t *TableHeader){
    int probe_type = TableHeader->probe_type;
    if(probe_type==CHAIN){
        return 0;
    }else{
        if(TableHeader->num_keys>=(TableHeader->table_size - 1)){
            return 1;
        }else{
            return 0;
        }
    }
}



/* Returns the number of table entries marked as deleted.  
 *
 * For separate chaining the number of delete keys is always zero.
 *
 * For lab6 experiments, this function is rarely called.  So it is
 * acceptable for this project to just scan the table and count the 
 * number entries deleted when the function is called.  
 */
int table_deletekeys(table_t *TableHeader){
    int probe_type = TableHeader->probe_type;
    int table_size = TableHeader->table_size;
    int i;
    int count = 0;
    if(probe_type!=CHAIN){
        elem_t *TableElements = (elem_t *)(TableHeader->table_elements);
        for(i=0;i<table_size;i++){
            if((TableElements + i)->status==DELETED){
                count++;
            }
        }
    }
    //printf("deleted keys %d\n", count);
    return count;
}
   


/* Insert a new table entry (K, I) into the table provided the table is not
 * already full.  
 * Return:
 *      0 if (K, I) is inserted, 
 *      1 if an older (K, I) is already in the table (update with the new I), or 
 *     -1 if the (K, I) pair cannot be inserted.
 *
 * Note that both K and I are pointers to memory blocks created by malloc().
 *
 * If the return result is 1, you must free the memory blocks that are no
 * longer needed.
 *
 * If the return result is -1, the caller will handle the memory blocks.  The
 * caller may need to examine the blocks to determine what failed. 
 */
int table_insert(table_t *TableHeader, hashkey_t Key, data_t Data){
    if(Key==NULL){
        return -1;
    }

    int probe_type = TableHeader->probe_type;
    int table_size = TableHeader->table_size;
    int index;

    TableHeader->recent_probes = 0;


    //printf("insert start\n");
    if(probe_type==CHAIN){                
        index = hashes_table_pos(Key,table_size);
        if(index>(table_size - 1)){
            return -1;
        }
        elem_t **TableElement = (elem_t **)(TableHeader->table_elements);
        elem_t *ListElement = *(TableElement + index);
        elem_t *previous;
        while(ListElement!=NULL){

            if(ListElement->status==EMPTY){
                ListElement->data = Data;
                ListElement->hashkey = Key;
                ListElement->status = OCCUPIED;
                TableHeader->num_keys = TableHeader->num_keys + 1;
                return 0;
            }else if(strcmp(ListElement->hashkey,Key)==0){
                free(ListElement->data);
                ListElement->data = Data;
                return 1;
            }

            (TableHeader->recent_probes)++;
            previous = ListElement;
            ListElement = ListElement->next;
        }

        ListElement = (elem_t *)malloc(sizeof(elem_t));
        ListElement->data = Data;
        ListElement->status = OCCUPIED;
        ListElement->hashkey = Key;
        ListElement->next = NULL;
        previous->next = ListElement;
        TableHeader->num_keys = TableHeader->num_keys + 1;
        return 0;
    }else{
        //printf("\tinsert start\n");
        index = hashes_table_pos(Key,table_size);

        int increment;
        if(probe_type==LINEAR){
            increment = 1;
        }else{
            increment = hashes_probe_dec(Key, table_size);
        }
        elem_t *TableElement = (elem_t *)(TableHeader->table_elements);
        TableElement = TableElement + index;
        int flag = 0;
        int count = 0;
        if(table_search(TableHeader, Key)!=NULL){
            //printf("recent probes %d\n",TableHeader->recent_probes);
            //printf("item already in table\n");
            while(flag!=2){
                //printf("index %d\n",index - count);
                if(TableElement->status==OCCUPIED){
                    //printf("occupied\n");
                    
                    if(strcmp(TableElement->hashkey,Key)==0){
                        //printf("\tduplicate found\n");
                        free(TableElement->data);
                        TableElement->data = Data;
                        return 1;                        
                    }
                }
                count = count + increment;
                if((index - count)<0){
                    //printf("\tlooping\n");
                    //getchar();
                    TableElement = (elem_t *)(TableHeader->table_elements) + table_size - 1 + (index - count + 1);
                    index = table_size - 1 + (index - count + 1);
                    count = 0;
                }else{
                    //printf("\tdeinc\n");
                    TableElement = TableElement - increment;
                }

            }
        }
        if((index>(table_size - 1))||(table_full(TableHeader))){
            return -1;
        }
        elem_t *compare = TableElement;
        while(flag!=2){
            //printf("index %d\n",index - count);
            if(TableElement->status==EMPTY||TableElement->status==DELETED){
                //printf("\tempty found\n");
                TableElement->hashkey = Key;
                TableElement->status = OCCUPIED;
                TableElement->data = Data;
                TableHeader->num_keys = TableHeader->num_keys + 1;
                //TableHeader->recent_probes = TableHeader->recent_probes - newindex;
                return 0;
            }else if(TableElement->status==OCCUPIED && (strcmp(TableElement->hashkey,Key)==0)){
                //printf("\tduplicate found\n");
                free(TableElement->data);
                TableElement->data = Data;
                //TableHeader->recent_probes = TableHeader->recent_probes - newindex;
                return 1;                
            }else{
                count = count + increment;
                if(TableElement == compare){
                    flag++;
                    if(flag==2){
                        return -1;
                    }
                }
                if((index - count)<0){
                    //printf("\tlooping\n");
                    TableElement = (elem_t *)(TableHeader->table_elements) + table_size - 1 + (index - count + 1);
                    index = table_size - 1 + (index - count + 1);
                    count = 0;
                    (TableHeader->recent_probes)++;
                }else{
                    //printf("\tdeinc\n");
                    TableElement = TableElement - increment;
                    (TableHeader->recent_probes)++;
                }

            }
        }
    }
    return -1;
}



/* Delete the table entry (K, I) from the table.  Free the key in the table.
 * Return:
 *     pointer to I, or
 *     null if (K, I) is not found in the table.  
 *
 * Be sure to free(K)
 *
 * See the note on page 490 in Standish's book about marking table entries for
 * deletions when using open addressing.  Review the -d driver for examples
 * of troublesome cases.
 */
data_t table_delete(table_t *TableHeader, hashkey_t Key){
    TableHeader->recent_probes = 0;
    int probe_type = TableHeader->probe_type;
    int table_size = TableHeader->table_size;
    int index;
    //printf("delete start\n");
    if(probe_type==CHAIN){
        index = hashes_table_pos(Key, table_size);
        elem_t **TableElement = ((elem_t **)(TableHeader->table_elements) + index);
        elem_t *ListElement = *TableElement;
        elem_t *prev = NULL;
        data_t temp;
        while(ListElement!=NULL){
            //printf("looped\n");
            //printf("status %d\n",ListElement->status);
            //printf("key %s\n",ListElement->hashkey);
            //printf("key %s\n",Key);
            //printf("%d\n",strcmp(ListElement->hashkey,Key));
            if((ListElement->status==OCCUPIED)&&(strcmp(ListElement->hashkey,Key)==0)){
                //printf("match\n");
                free(ListElement->hashkey);
                TableHeader->num_keys = TableHeader->num_keys - 1;
                temp = ListElement->data;
                ListElement->status = EMPTY;   

                if(prev==NULL){
                    //printf("prev==NULL\n");
                    if(ListElement->next!=NULL){
                        *TableElement = ListElement->next;
                        free(ListElement);
                        return temp;
                    }else{
                        ListElement->status = EMPTY;
                        return temp;
                    }
                }else{
                    prev->next = ListElement->next;
                    free(ListElement);
                    return temp;
                }
            }
            (TableHeader->recent_probes)++;
            prev = ListElement;
            ListElement = ListElement->next;
        }
        return NULL;
    }else{
        index = hashes_table_pos(Key, table_size);

        int increment;
        if(probe_type==LINEAR){
            increment = 1;
        }else{
            increment = hashes_probe_dec(Key, table_size);
        }
        
        elem_t *TableElement =((elem_t *)(TableHeader->table_elements) + index);
        data_t temp;
        elem_t *compare = TableElement;
        int count = 0;
        int flag = 0;
        while(flag!=2){
            if(TableElement->status==OCCUPIED){
                //printf("item found\n");
                if(strcmp(TableElement->hashkey,Key)==0){
                    TableHeader->num_keys = TableHeader->num_keys - 1;
                    //printf("item deleted\n");
                    free(TableElement->hashkey);
                    temp = TableElement->data;
                    TableElement->data = NULL;
                    TableElement->status = DELETED;
                    //TableHeader->recent_probes = TableHeader->recent_probes - newindex;
                    return temp;
                }   
            }else if(TableElement->status==EMPTY){
                return NULL;
            }
            
            if(flag<=2){
                count = count + increment;
                if(TableElement == compare){
                    flag++;
                    if(flag==2){
                        return NULL;
                    }
                }               
                if((index - count)<0){
                    TableElement = ((elem_t *)(TableHeader->table_elements) + table_size - 1) + (index - count + 1);
                    index = table_size - 1 + (index - count + 1);
                    count = 0;
                    (TableHeader->recent_probes)++;            
                }else{
                    TableElement = TableElement - increment;
                    (TableHeader->recent_probes)++;
                }
            }else{
                //TableHeader->recent_probes = TableHeader->recent_probes - newindex;
                return NULL;
            }
            
        }
    }
    return NULL;
}



/* Given a key, K, retrieve the pointer to the information, I, from the table,
 * but do not remove (K, I) from the table.  Return NULL if the key is not
 * found.
 */
data_t table_search(table_t *TableHeader, hashkey_t Key){
    int probe_type = TableHeader->probe_type;
    int table_size = TableHeader->table_size;
    int index;

    TableHeader->recent_probes = 0;
    //printf("search start\n");
    if(probe_type==CHAIN){
        index = hashes_table_pos(Key, table_size);
        elem_t **TableElement = ((elem_t **)(TableHeader->table_elements) + index);
        elem_t *ListElement = *TableElement;
        int i = 0;
        while(ListElement!=NULL){
            if(ListElement->status==OCCUPIED&&strcmp(ListElement->hashkey,Key)==0){
                return ListElement->data;         
            }
            (TableHeader->recent_probes)++;
            ListElement = ListElement->next;
            i++;
        }
        return NULL;
    }else{
        index = hashes_table_pos(Key, table_size);
        int increment;
        if(probe_type==LINEAR){
            increment = 1;
        }else{
            increment = hashes_probe_dec(Key, table_size);
        }
        elem_t *TableElement = ((elem_t *)(TableHeader->table_elements) + index);
        elem_t *compare = TableElement;
        int count = 0;
        int flag = 0;
        int newindex = index;
        
        while(flag!=2){
            //printf("index %d\n",newindex - count);
            if(TableElement->status==EMPTY){
                return NULL;
            }
            if(TableElement->status==OCCUPIED){
                //printf("element occupied\n");
                if(strcmp(TableElement->hashkey,Key)==0){
                    //printf("found key\n");
                    //TableHeader->recent_probes = TableHeader->recent_probes - index;
                    return TableElement->data;
                }
            }
            if(flag<=2){
                count = count + increment;
                if(TableElement==compare){
                    flag++;
                    if(flag==2){
                        return NULL;
                    }
                }
                if((newindex - count)<0){
                    //printf("looping\n");
                    TableElement = ((elem_t *)(TableHeader->table_elements) + table_size - 1) + (newindex - count + 1);
                    newindex = table_size - 1 + (newindex - count + 1);
                    count = 0;
                    (TableHeader->recent_probes)++;
                }else{
                    //printf("deinc\n");
                    TableElement = TableElement - increment;
                    (TableHeader->recent_probes)++;
                }
            }else{
                //printf("key not found\n");
                //TableHeader->recent_probes = TableHeader->recent_probes - index;
                return NULL;
            }
            
        }
    }
    return NULL;
}



/* Free all information in the table, the table itself, and any additional
 * headers or other supporting data structures.  
 */
void table_destruct(table_t *TableHeader){
    int probe_type = TableHeader->probe_type;
    int table_size = TableHeader->table_size;
    int i;
    if(probe_type==CHAIN){
        elem_t **TableElements = (elem_t **)(TableHeader->table_elements);
        elem_t *rover;
        elem_t *prev;
        for(i=0;i<table_size;i++){
            rover = *(TableElements + i);
            while(rover!=NULL){
                prev = rover;
                rover = rover->next;
                if(prev->status==OCCUPIED){
                    if(prev->hashkey!=NULL)free(prev->hashkey);
                    if(prev->data!=NULL)free(prev->data);
                }
                free(prev);
            }
        }
        free(TableElements);
    }else{
        elem_t *TableElements = (elem_t *)(TableHeader->table_elements);
        for(int i=0;i<TableHeader->table_size;i++){
            if((TableElements + i)->status==OCCUPIED){
                if((TableElements + i)->hashkey!=NULL)free((TableElements + i)->hashkey);
                if((TableElements + i)->data!=NULL)free((TableElements + i)->data);                
            }
        }
        free(TableElements);
    }
    free(TableHeader); 
}



/* The number of probes for the most recent call to table_search,
 * table_insert, or table_delete 
 *
 * Due to a quirk in the way Standish has defined comparisons in his 
 * performance formulas, we have two different rules for counting probes.  
 * For open addressing the function must return the number of probes into the 
 * hash table (that is, the number of comparisons includes checking if a 
 * position contains an empty key (or is marked as deleted) even if the empty 
 * is represented by a NULL pointer).  For separate chaining, count the number
 * of key comparisons required to insert, search or delete (and don’t count 
 * tests for a NULL pointer).
 */
int table_stats(table_t *TableHeader){
    return TableHeader->recent_probes;
}



/* This function is for testing purposes only.  Given an index position into
 * the hash table return the value of the key if data is stored in this 
 * index position.  If the index position does not contain data, then the
 * return value must be zero.  
 *
 * For separate chaining, return the key found in list_position at this index 
 * position.  If the list_position is 0, the function returns the first key in
 * the linked list; if 1 the second key, etc.  If the list_position is greater
 * than the number of items in the list, then return NULL.  Notice 
 * list_position is not used for open addressing
 *
 * Make the first lines of this function 
 *       assert(0 <= index && index < table_size); 
 *       assert(0 <= list_position); 
 */
hashkey_t table_peek(table_t *TableHeader, int index, int list_position){
    assert(0 <= index && index < TableHeader->table_size); 
    assert(0 <= list_position); 
    if(TableHeader->probe_type==CHAIN){
        elem_t **TableElement;
        TableElement = (elem_t **)TableHeader->table_elements;
        TableElement = TableElement + index;
        elem_t *ListElement;
        ListElement = *TableElement;
        //printf("index %d, %d\n",index,list_position);
        for(int i=0;i<list_position;i++){
            if(ListElement==NULL||ListElement->status==EMPTY){
                //printf("not found\n");
                return NULL;
            }
            //printf("next\n");
            ListElement = ListElement->next;
        }
        if(ListElement!=NULL&&ListElement->status==OCCUPIED){
            //printf("found\n");
            return ListElement->hashkey;
        }else{
            //printf("not found\n");
            return NULL;
        }
    }else{
        elem_t *TableElement;
        TableElement = (elem_t *)TableHeader->table_elements;
        TableElement = TableElement + index;
        if(TableElement->status==OCCUPIED){
            return TableElement->hashkey;
        }else{
            return NULL;
        }
    }
}



/* Print the table position and keys in a easily readable and compact format.
 * Distinguish between empty and deleted locations.
 * Only useful when the table is small.
 */
void table_debug_print(table_t *TableHeader){
    int i;
    if(TableHeader->probe_type==CHAIN){
        int j;
        elem_t **TableElement;
        TableElement = (elem_t **)TableHeader->table_elements;
        elem_t *ListElement;
        for(i=0;i<TableHeader->table_size;i++){
            ListElement = *(TableElement + i);
            j=0;
            while(ListElement!=NULL){
                if(ListElement->status==EMPTY){
                    printf("Table[%d][%d] = EMPTY, ",i,j);
                }else{
                    printf("Table[%d][%d] = %s, ",i,j,ListElement->hashkey);
                }
                j++;
                ListElement = ListElement->next;
            }   
            printf("\n");
        }
    }else{
        elem_t *TableElement;
        TableElement = (elem_t *)TableHeader->table_elements;
        for(i=0;i<TableHeader->table_size;i++){
            if((TableElement + i)->status==NKEY){
                printf("Table[%d] = NULL\n",i);
            }else if((TableElement + i)->status==DELETED){
                printf("Table[%d] = DELETED\n",i);
            }else if((TableElement + i)->data==NULL){
                printf("Table[%d] = EMPTY\n",i);
            }else{
                printf("Table[%d] = %s\n",i,(TableElement + i)->hashkey);
            }
        }
    }
}

