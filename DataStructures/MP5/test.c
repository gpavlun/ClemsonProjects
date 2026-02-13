#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "header.h"

void stats(tree_t *yggdrasil){
    printf("\n===TREE===\n#comparisons - %d\n#keys - %d\naddress - %lX\n==========\n\n",yggdrasil->ncomps,yggdrasil->nkeys,(long)(yggdrasil->well));
}

int main(void){

    tree_t *yggdrasil = tree_construct();
    data_t data = 10;
    data_t *data_ptr = &data;
    int succ;
    for(int i=0; i<10; i++){
        int x = rand() % (50-10+1)+10;
        printf("%d) key - %d ",i,x);
        succ = tree_insert(yggdrasil,x,data_ptr);
        succ ? printf("[1] ") : printf("[0] ");
    }
    printf("\n");
    
    stats(yggdrasil);
    printf("**pathlength == %d\n", tree_internal_path_len(yggdrasil));
    print_tree(yggdrasil);
     for(int i=0; i<20; i++){
         int x = rand() % (50-10+1)+10;
         printf("%d) key - %d ",i,x);
         data_ptr = tree_remove(yggdrasil,x);
         data_ptr!=NULL ? printf("[1] ") : printf("[0] ");
     }
     printf("\n");
    
    stats(yggdrasil);

    printf("**pathlength == %d\n", tree_internal_path_len(yggdrasil));
    print_tree(yggdrasil);


    
    return 0;
    
}