#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "hashes.h"

int main(void){

    table_t *TableHeader = table_construct(10,0);
    printf("building table of type %d with size %d\n",TableHeader->probe_type,TableHeader->table_size);
    table_debug_print(TableHeader);
    printf("--all empty\n\n");
    printf("attempting to insert in every position\n");
    hashkey_t hashkey;
    data_t data;
    int test;
    for(int i=0;i<(TableHeader->table_size);i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        data = (int *)malloc(sizeof(int));
        *data = 1111;
        test = table_insert(TableHeader,hashkey,data);
        if(test==0){
            printf("\tkey %c inserted, starting at %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
        }else if(test==1){
            printf("\tkey %c updated\n",hashkey[0]);
        }else{
            printf("\tkey %c did not insert\n",hashkey[0]);
        }
    }
    printf("table is full\n");
    table_debug_print(TableHeader);
    printf("--allowed all but one to insert\n\n");
    printf("deleting one item\n");

    data_t test2 = table_delete(TableHeader,"g");
    if(test2==NULL){
        printf("\tkey %c not in table\n",'g');
    }else{
        printf("\tkey %c removed\n",'g');
    }
    printf("table has one deleted item\n");
    table_debug_print(TableHeader);
    data = (int *)malloc(sizeof(int));
    *data = 1111;
    strcpy(hashkey,"h");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item already in table\n");
    if(test==0){
        printf("\tkey %c inserted\n",hashkey[0]);
    }else if(test==1){
        printf("\tkey %c updated\n",hashkey[0]);
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }
    printf("table with updated key\n");
    table_debug_print(TableHeader);
    strcpy(hashkey,"k");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item in table\n");
    if(test==0){
        printf("\tkey %c inserted, starting at %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
    }else if(test==1){
        printf("\tkey %c updated\n",hashkey[0]);
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }
    printf("table with k inserted\n");
    table_debug_print(TableHeader);
    printf("--only one empty spot, deleted\n\n");

    printf("delete three items\n");
    for(int i=0;i<(3);i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        test2 = table_delete(TableHeader,hashkey);
        if(test2==NULL){
            printf("\tkey %c not in table\n",hashkey[0]);
        }else{
            printf("\tkey %c removed\n",hashkey[0]);
        }
    }
    printf("table after deletions\n");
    table_debug_print(TableHeader);
    printf("--table with 4 deleted spots\n\n");

    printf("rehashing table to size 22\n");
    table_rehash(TableHeader,22);
    printf("table after rehash\n");
    table_debug_print(TableHeader);
    printf("--no deleteds remain\n\n");

    printf("rehash to a size of 6\n");
    table_rehash(TableHeader,6);
    printf("table after rehashing\n");
    table_debug_print(TableHeader);
    printf("--key k was not able to be reinserted\n\n");

    printf("attmept delete 10 items\n");
    for(int i=0;i<10;i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        test2 = table_delete(TableHeader,hashkey);
        if(test2==NULL){
            printf("\tkey %c not in table\n",hashkey[0]);
        }else{
            printf("\tkey %c removed\n",hashkey[0]);
        }
    }
    printf("table after deletions\n");
    table_debug_print(TableHeader);
    printf("--no more items in table\n");
    printf("--did not try to delete items that didn't exist\n");






    table_destruct(TableHeader);
    TableHeader = table_construct(10,1);
    printf("\n\n\nbuilding table of type %d with size %d\n",TableHeader->probe_type,TableHeader->table_size);
    table_debug_print(TableHeader);
    printf("--all empty\n\n");
    printf("attempting to insert in every position\n");

    for(int i=0;i<(TableHeader->table_size);i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        data = (int *)malloc(sizeof(int));
        *data = 1111;
        test = table_insert(TableHeader,hashkey,data);
        if(test==0){
            printf("\tkey %c inserted, starting at %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
        }else if(test==1){
            printf("\tkey %c updated\n",hashkey[0]);
        }else{
            printf("\tkey %c did not insert\n",hashkey[0]);
        }
    }
    printf("table is full\n");
    table_debug_print(TableHeader);
    printf("--allowed all but one to insert\n\n");
    printf("deleting one item\n");

    test2 = table_delete(TableHeader,"g");
    if(test2==NULL){
        printf("\tkey %c not in table\n",'g');
    }else{
        printf("\tkey %c removed\n",'g');
    }
    printf("table has one deleted item\n");
    table_debug_print(TableHeader);
    data = (int *)malloc(sizeof(int));
    *data = 1111;
    strcpy(hashkey,"h");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item already in table\n");
    if(test==0){
        printf("\tkey %c inserted\n",hashkey[0]);
    }else if(test==1){
        printf("\tkey %c updated\n",hashkey[0]);
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }
    printf("table with updated key\n");
    table_debug_print(TableHeader);
    strcpy(hashkey,"k");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item in table\n");
    if(test==0){
        printf("\tkey %c inserted, starting at %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
    }else if(test==1){
        printf("\tkey %c updated\n",hashkey[0]);
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }
    printf("table with k inserted\n");
    table_debug_print(TableHeader);
    printf("--only one empty spot, deleted\n\n");

    printf("delete three items\n");
    for(int i=0;i<(3);i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        test2 = table_delete(TableHeader,hashkey);
        if(test2==NULL){
            printf("\tkey %c not in table\n",hashkey[0]);
        }else{
            printf("\tkey %c removed\n",hashkey[0]);
        }
    }
    printf("table after deletions\n");
    table_debug_print(TableHeader);
    printf("--table with 4 deleted spots\n\n");

    printf("rehashing table to size 22\n");
    table_rehash(TableHeader,22);
    printf("table after rehash\n");
    table_debug_print(TableHeader);
    printf("--no deleteds remain\n\n");

    printf("rehash to a size of 6\n");
    table_rehash(TableHeader,6);
    printf("table after rehashing\n");
    table_debug_print(TableHeader);
    printf("--key k was not able to be reinserted\n\n");

    printf("attmept delete 10 items\n");
    for(int i=0;i<10;i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        test2 = table_delete(TableHeader,hashkey);
        if(test2==NULL){
            printf("\tkey %c not in table\n",hashkey[0]);
        }else{
            printf("\tkey %c removed\n",hashkey[0]);
        }
    }
    printf("table after deletions\n");
    table_debug_print(TableHeader);
    printf("--no more items in table\n");
    printf("--did not try to delete items that didn't exist\n");






    table_destruct(TableHeader);
    TableHeader = table_construct(10,2);
    printf("\n\n\nbuilding table of type %d with size %d\n",TableHeader->probe_type,TableHeader->table_size);
    table_debug_print(TableHeader);
    printf("--all empty\n\n");
    printf("attempting to insert in every position\n");

    for(int i=0;i<(TableHeader->table_size);i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        data = (int *)malloc(sizeof(int));
        *data = 1111;
        test = table_insert(TableHeader,hashkey,data);
        if(test==0){
            printf("\tkey %c inserted, starting at %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
        }else if(test==1){
            printf("\tkey %c updated, starting at %d\n\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
        }else{
            printf("\tkey %c did not insert\n",hashkey[0]);
        }
    }
    printf("table is not full\n");
    table_debug_print(TableHeader);
    printf("--allowed all to insert\n\n");
    printf("deleting one item\n");

    test2 = table_delete(TableHeader,"g");
    if(test2==NULL){
        printf("\tkey %c not in table\n",'g');
    }else{
        printf("\tkey %c removed\n",'g');
    }
    printf("table has one deleted item\n");
    table_debug_print(TableHeader);
    data = (int *)malloc(sizeof(int));
    *data = 1111;
    hashkey = (hashkey_t)malloc(sizeof(char)*2);
    strcpy(hashkey,"h");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item already in table\n");
    if(test==0){
        printf("\tkey %c inserted, starting at %d\n\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
    }else if(test==1){
        printf("\tkey %c updated, starting at %d\n\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }
    printf("table with updated key\n");
    table_debug_print(TableHeader);


    hashkey = (hashkey_t)malloc(sizeof(char)*2);
    strcpy(hashkey,"k");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item in table\n");
    if(test==0){
        printf("\tkey %c inserted, starting at %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
    }else if(test==1){
        printf("\tkey %c updated, starting at %d\n\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size));
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }
    printf("table with k inserted\n");
    table_debug_print(TableHeader);
    printf("--only one empty spot\n\n");

    printf("delete three items\n");
    for(int i=0;i<(3);i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        test2 = table_delete(TableHeader,hashkey);
        if(test2==NULL){
            printf("\tkey %c not in table\n",hashkey[0]);
        }else{
            printf("\tkey %c removed\n",hashkey[0]);
        }
    }
    printf("table after deletions\n");
    table_debug_print(TableHeader);
    printf("--table with 4 deleted spots\n\n");

    printf("rehashing table to size 22\n");
    table_rehash(TableHeader,22);
    printf("table after rehash\n");
    table_debug_print(TableHeader);
    printf("--no deleteds remain\n\n");

    printf("rehash to a size of 6\n");
    table_rehash(TableHeader,6);
    printf("table after rehashing\n");
    table_debug_print(TableHeader);
    printf("--all keys able to be reinserted\n\n");

    printf("attmept delete 10 items\n");
    for(int i=0;i<10;i++){
        hashkey = (hashkey_t)malloc(sizeof(char)*2);
        hashkey[0] = i + 97;
        hashkey[1] = 0;
        test2 = table_delete(TableHeader,hashkey);
        if(test2==NULL){
            printf("\tkey %c not in table\n",hashkey[0]);
        }else{
            printf("\tkey %c removed\n",hashkey[0]);
        }
    }
    printf("table after deletions\n");
    table_debug_print(TableHeader);
    printf("--only k remains\n");
    printf("--did not try to delete items that didn't exist\n");



    table_destruct(TableHeader);
    TableHeader = table_construct(4,1);
    printf("\n\n\nbuilding table of type %d with size %d\n",TableHeader->probe_type,TableHeader->table_size);
    hashkey = (hashkey_t)malloc(sizeof(char)*2);
    strcpy(hashkey,"k");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item in table\n");
    if(test==0){
        printf("\tkey %c inserted, starting at %d, increment %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size),TableHeader->table_size);
    }else if(test==1){
        printf("\tkey %c updated, starting at %d, increment %d\n\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size),TableHeader->table_size);
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }

    table_debug_print(TableHeader);
    hashkey = (hashkey_t)malloc(sizeof(char)*2);
    strcpy(hashkey,"c");
    test = table_insert(TableHeader,hashkey,data);
    printf("attempt to insert item in table\n");
    if(test==0){
        printf("\tkey %c inserted, starting at %d, increment %d\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size),TableHeader->table_size);
    }else if(test==1){
        printf("\tkey %c updated, starting at %d, increment %d\n\n",hashkey[0],hashes_table_pos(hashkey,TableHeader->table_size),TableHeader->table_size);
    }else{
        printf("\tkey %c did not insert\n",hashkey[0]);
    }
    table_debug_print(TableHeader);















    return 1;
}