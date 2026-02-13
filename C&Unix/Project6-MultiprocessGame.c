#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void InputVerification(int argc, char* argv[]){

    /*checks to make sure they actually typed something*/
    if(argc==1){
        printf("not enough arguments\n");
        exit(0);
    }
    /*check to see if the command is correct*/
    if((strcmp(argv[1],"read")!=0)&&(strcmp(argv[1],"edge")!=0)&&(strcmp(argv[1],"noise")!=0)){

        printf("first command must be \"read\", \"edge\", or \"noise\"\n");
        exit(0);

    }else if((strcmp(argv[1],"read")==0)&&(argc!=4)){/*if the command is "read"*/

        if(argc>4){

            printf("too many arguments\n");

        }else{

            printf("must include input and output file\n");

        }

        exit(0);

    }else if((strcmp(argv[1],"read")!=0)&&(argc!=3)){/*if the command is either noise or edge*/
        if(argc>3){

            printf("too many arguments\n");

        }else{

            printf("must include input file\n");

        }

        exit(0);

    }
}

void main(int argc, char* argv[]){
    /*verify the command line arguments*/
    InputVerification(argc, argv);
}