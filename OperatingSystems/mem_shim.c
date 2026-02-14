#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

struct node{
    struct node *next;
    size_t nbytes;
    void *address;
};
struct header{
    struct node *list;
    int count;
};
struct header *Header;
struct node *List;
/*
constructor runs at load time and will create the linked list
*/
__attribute__((constructor))
void *initialize(void){
    static void *(*system_malloc)(size_t) = NULL;
    if(!system_malloc){
        system_malloc = dlsym(RTLD_NEXT, "malloc");
        if(!system_malloc) write(1,"dlsym error {malloc,init}\n", 26);
    }
    Header = system_malloc(sizeof(struct header));
    Header->count = 0;
    Header->list = NULL;
    return NULL;
}
/*
destructor will print out the leaks and free the list at end
of the program
*/
__attribute__((destructor))
void *debrief(void){
    static void (*system_free)(void *) = NULL;
    !system_free?({
        system_free = dlsym(RTLD_NEXT, "free");
        !system_free?({write(1,"dlsym error {free,free}\n", 24);}):0;
    }):0;
    struct node *Ratatosk = Header->list;
    struct node *Ksotatar = NULL;
    for(int i=0;i<Header->count;i++){
        Ksotatar = Ratatosk;
        fprintf(stderr, "LEAK\t%zu @ %p\n", Ratatosk->nbytes,Ratatosk->address);
        Ratatosk = Ratatosk->next;
        system_free(Ksotatar);
    }
    system_free(Header);
    return NULL;
}


/*
intercepts malloc and records the calls in the linked list
*/
void *malloc(size_t size){
    static void *(*system_malloc)(size_t) = NULL;
    !system_malloc?({
        system_malloc = dlsym(RTLD_NEXT, "malloc");
        !system_malloc?({
            write(1,"dlsym error {malloc,malloc}\n", 28);
        }):0;
    }):0;
    void *temp = system_malloc(size);

    List = Header->list;
    if(List){
        while(List->next){
            List = List->next;
        }
    }

    temp?({
        !Header->list?({
            Header->list = system_malloc(sizeof(struct node));
            List = Header->list;
        }):({
            !List->next?({
                List->next = system_malloc(sizeof(struct node));
                List = List->next;
            }):0;
        });
        List->address = temp;
        List->nbytes = size;
        List->next = NULL;
        Header->count++;
    }):0;
    return temp;  
}
/*
virtually identical to the malloc one
*/
void *calloc(size_t count,size_t size){
    static void *(*system_calloc)(size_t,size_t) = NULL;
    !system_calloc?({
        system_calloc = dlsym(RTLD_NEXT, "calloc");
        !system_calloc?({write(1,"dlsym error {calloc,calloc}\n", 28);}):0;
    }):0;
    void *temp = system_calloc(count,size);
    
    List = Header->list;
    if(List){
        while(List->next){
            List = List->next;
        }
    }
    
    temp?({
        !Header->list?({
            Header->list = system_calloc(1,sizeof(struct node));
            List = Header->list;
        }):({
            !List->next?({
                List->next = system_calloc(1,sizeof(struct node));
                List = List->next;
            }):0;
        });
        List->address = temp;
        List->nbytes = count*size;
        List->next = NULL;
        Header->count++;
    }):0;
    return temp;  
}
/*
realloc will update the memory block in the list 
with the new size and address if it is found.
*/
void *realloc(void *pointer, size_t size){
    static void (*system_free)(void *) = NULL;
    !system_free?({
        system_free = dlsym(RTLD_NEXT, "free");
        !system_free?({write(1,"dlsym error {free,free}\n", 24);}):0;
    }):0;
    static void *(*system_malloc)(size_t) = NULL;
    !system_malloc?({
        system_malloc = dlsym(RTLD_NEXT, "malloc");
        !system_malloc?({
            write(1,"dlsym error {malloc,malloc}\n", 28);
        }):0;
    }):0;
    static void *(*system_realloc)(void *,size_t) = NULL;
    !system_realloc?({
        system_realloc = dlsym(RTLD_NEXT, "realloc");
        !system_realloc?({write(1,"dlsym error {realloc,realloc}\n", 28);}):0;
    }):0;

    void *temp = pointer;
    temp = system_realloc(pointer, size);

    temp?({
        struct node *Ratatosk = Header->list;
        struct node *ksotataR = NULL;
        if(Ratatosk){
            if(Ratatosk->address==pointer){
                Header->list = Ratatosk->next;
                system_free(Ratatosk);
            }else{
                while(Ratatosk->next){
                    if(Ratatosk->next->address==pointer){
                        ksotataR = Ratatosk->next->next;
                        system_free(Ratatosk->next);
                        Ratatosk->next = ksotataR;
                        break;
                    }else{
                        Ratatosk = Ratatosk->next;
                    }
                }
            }
        }

        List = Header->list;
        if(List){
            while(List->next){
                List = List->next;
            }
        }
        !Header->list?({
            Header->list = system_malloc(sizeof(struct node));
            List = Header->list;
        }):({
            !List->next?({
                List->next = system_malloc(sizeof(struct node));
                List = List->next;
            }):0;
        });
        List->address = temp;
        List->nbytes = size;
        List->next = NULL;
        Header->count++;
    }):0;
    return temp;
}
/*
free will remove an item from the linked list if 
it is found
*/
void free(void *pointer){ 
    static void (*system_free)(void *) = NULL;
    !system_free?({
        system_free = dlsym(RTLD_NEXT, "free");
        !system_free?({write(1,"dlsym error {free,free}\n", 24);}):0;
    }):0;
    system_free(pointer);
    struct node *Ratatosk = Header->list;
    struct node *ksotataR = NULL;
    if(pointer){
        if(Ratatosk){
            if(Ratatosk->address==pointer){
                Header->list = Ratatosk->next;
                system_free(Ratatosk);
            }else{
                while(Ratatosk->next){
                    if(Ratatosk->next->address==pointer){
                        ksotataR = Ratatosk->next->next;
                        system_free(Ratatosk->next);
                        Ratatosk->next = ksotataR;
                        break;
                    }else{
                        Ratatosk = Ratatosk->next;
                    }
                }
            }
        }
    }
}
