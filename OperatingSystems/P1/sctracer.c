#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/ptrace.h>
#include <linux/ptrace.h>

#include <sys/wait.h>

struct node{
    struct node *next;
    int ncalls;
    long long callID;
};
struct header{
    struct node *list;
};


int main(int argc, char **argv) {
    int i;
    if(argc!=3){
        printf("usage:\n\t./sctracer ./my_random_test_program <output_file>\nor\n");
        printf("\t./sctracer \"./my_test_program arg1 arg2\" <output_file>\n");
        return 1;
    }
    char **arguments = malloc(sizeof(char *));
    char *parser = argv[1];
    char *argstart = parser;
    int nargs = 0;
    i=1;

    /*
    parses the second arg into a list of
    args that can be passed to the forked
    off process
    */
    while(*parser){
        parser++;
        if((*parser)==' '||(*parser)=='\0'){
            
            *(arguments + nargs) = malloc(96);
            strncpy(*(arguments + nargs), argstart, i);
            
            *(*(arguments+nargs) + i) = 0;

            nargs++;
            i = 0;

            argstart = parser;
            while((*argstart)==' '){
                argstart++;
            }
            if(parser){
                arguments = realloc(arguments, sizeof(char *)*(nargs+1));
                *(arguments + nargs) = NULL;
            }
        }else{
            i++;
        }
    }

    /*
    forks off the child process from arg 2
    */
    int ChildID = fork();
    if(ChildID==-1){
        printf("ERROR: fork failed\n");
        return 1;
    }
    if (!ChildID) {

        ptrace(PTRACE_TRACEME);
        kill(getpid(), SIGSTOP);
 
        ChildID = getpid();

        if(execvp(arguments[0], &(arguments[0]))==-1){
            fprintf(stdout,"ERROR: exec failed\n");
            return 1;
        }
    } else {
        /*
        parent creates the linked list and stores all the 
        system calls in it
        */
        struct header *Header = malloc(sizeof(struct header));
        struct node *Ratatosk = NULL;
        struct node *Ksotatar = NULL;
        Header->list = NULL;

        int ChildStatus;
        long long SysCallID;
        waitpid(ChildID, &ChildStatus, 0);
        ptrace(PTRACE_SETOPTIONS, ChildID, 0, PTRACE_O_TRACESYSGOOD);

        struct ptrace_syscall_info RegisterInfo;

        /*
        infinite loop counts any calls until the process exits
        */
        while(1){
            ptrace(PTRACE_SYSCALL, ChildID, 0, 0);
            waitpid(ChildID, &ChildStatus, 0);

            WIFEXITED(ChildStatus)?({goto exit;}):0;

            ((!WIFSTOPPED(ChildStatus))||(!(WSTOPSIG(ChildStatus) & 0x80)))?({continue;}):0;

            ptrace(PTRACE_GET_SYSCALL_INFO, ChildID, sizeof(struct ptrace_syscall_info), &RegisterInfo);
            if (RegisterInfo.op != PTRACE_SYSCALL_INFO_ENTRY) {
                continue;
            }
            SysCallID = RegisterInfo.entry.nr;
            Ratatosk = Header->list;
            Ksotatar = NULL;

            if(!Ratatosk){
                Header->list = malloc(sizeof(struct node));
                Header->list->callID = SysCallID;
                Header->list->ncalls = 1;
                Header->list->next = NULL;
            }else{

                while(Ratatosk){
                    if(Ratatosk->callID==SysCallID){
                        Ratatosk->ncalls++;
                        break;
                    }else if(Ratatosk->callID<SysCallID){
                        Ksotatar = Ratatosk;
                        Ratatosk = Ratatosk->next;
                    }
                    if(!Ratatosk||Ratatosk->callID>SysCallID){
                        if(!Ksotatar){
                            Header->list = malloc(sizeof(struct node));
                            Header->list->next = Ratatosk;
                            Header->list->ncalls = 1;
                            Header->list->callID = SysCallID;
                            break;
                        }else{
                            Ksotatar->next = malloc(sizeof(struct node));
                            Ksotatar->next->next = Ratatosk;
                            Ksotatar->next->callID = SysCallID;
                            Ksotatar->next->ncalls = 1;
                            break;
                        }
                    }
                }
            }    
        }

        exit:
        /*
        prints the list out to the given
        file in the third arg
        */
        FILE *file = fopen(argv[2],"w");
        !file?({
            perror("fopen");
            exit(1);
        }):0;

        Ratatosk = Header->list;
        while(Ratatosk!=NULL){
            fprintf(file,"%lld\t%d\n",Ratatosk->callID,Ratatosk->ncalls);
            Ratatosk = Ratatosk->next;
        }
        fclose(file);
        exit(0);
    }
    return 0;
}

