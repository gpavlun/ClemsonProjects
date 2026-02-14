/*
name:     Gregory Pavlunenko
user:     gpavlun
course:   ECE2220
semester: fall
project:  4
purpose:  This project is designed to take a word and a cipher and 
          either encode or decode it based on that prompt
assumptions: For encoding, not much, but for decoding, we do assume
             that the cipher is the same lenght as the text
bugs: none I know of
notes: I wrote this entire thing in 3 hours, please have mercy I know the comments suck*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
function: ARG1
purpose: Checks to see if argument 1 is valid
*/
int ARG1(char arg[]){
    int same = 0;
    int type = 0;
    char Encode[] = "Encode";
    char Decode[] = "Decode";
    int i;
    
  
    if(strlen(arg)==strlen(Encode)){
        same = 1;
        for(i=0;i<6;i++){
            if(arg[i]!=Encode[i]){
                same = 0;
            }
        }
    }
    if(same==1){
        type = 1;
    }
    same = 0;
    if((type==0)&&(strlen(arg)==strlen(Decode))){
        same = 1;
        for(i=0;i<6;i++){
            if(arg[i]!=Decode[i]){
                same = 0;
            }
        }
    }
    if(same==1){
        type = 2;
    }
    if((type!=1)&&(type!=2)){
        printf("User did not type Encode or Decode\n");
        exit(0);
    }
    return type;
}
/*
function: checkchar
purpose: Checks to see if argument 2 and 3 are valid
*/
int checkchar(char arg[]){
    int i,l;
    l = strlen(arg);
    if(l>32){
        printf("arguments must be 32 characters or less");
        exit(0);
    }
    for(i=0;i<l;i++){
        if(((arg[i]<0x41||arg[i]>0x5A)&&(arg[i]<0x61||arg[i]>0x7A))&&arg[i]!=0x20){
            printf("Second & third argument must be in all letters or spaces\n");
            exit(0);
        }
    }
}
/*
function: stripwhite
purpose: strips white space and makes characters lowercase
*/
char *stripwhite(char arg[]){
    static char ret[32];
    int i,l,c=0;
    l=strlen(arg);
    //strips out white space
    for(i=0;i<l;i++){
        if(arg[i]==' '){
            c++;
        }
    }
    

    //subtracts dec 32 to make the uppercase ascii lowercase
    c=0;
    for(i=0;i<l;i++){
        if(arg[i]!=' '){
            if(arg[i]>0x60&&arg[i]<0x7B){
                ret[c]=arg[i]-32;
                c++;
            }else{
                ret[c]=arg[i];
                c++;
            }

        }
    }

    return ret;
}
/*
function: Encode
purpose: creates a matrix of letters and encodes it to the specification
*/
char *Encode(char Input[],char Code[]){


    
    char table[676][2];
    int i,j,k;
//create table
    for(k=0;k<26;k++){
        j = 0x41 + k;
        for(i=0;i<26;i++){
            if(j==0x5B){
                j = 0x41;
            }
            table[i+(k*26)][0]=j;
            table[i+(k*26)][1]='\0';
            j++;
            printf("%s",table[i+(k*26)]);
        }
        printf("\n");
    }


    static char Output[32];


    int l0 = strlen(Input);
    int l1 = strlen(Code);
//manually index table
    for(i=0,k=0;i<l0;i++,k++){
        if(k>l1){
            k = 0;
        }

        Output[i] = table[(Input[i]-65)*26+(Code[k]-65)][0];

    }
    return Output;
}


/*
function: Decode
purpose: creates a matrix of letters and decodes it to the specification
*/
char *Decode(char Input[],char Code[]){
    
    char table[676][2];
    int i,j,k;
    //create table
    for(k=0;k<26;k++){
        j = 0x41 + k;
        for(i=0;i<26;i++){
            if(j==0x5B){
                j = 0x41;
            }
            table[i+(k*26)][0]=j;
            table[i+(k*26)][1]='\0';
            j++;
            printf("%s",table[i+(k*26)]);
        }
        printf("\n");
    }


    static char Output[32];


    int l0 = strlen(Input);
    //find column label that contains row value
    for(i=0;i<l0;i++,k){
        j = (Code[i]-65)*26;
        for(k=0;k<26;k++){
            if(Input[i]==table[j+k][0]){
                Output[i] = table[k][0];
            }
        }

    }
    return Output;
}



void main(int argc, char *argv[]){

    if(argc!=4){
        printf("wrong arguement count\n");
        exit(0);
    }

    int type;
    char Input[32];
    char Code[32];
    char Output[32];
//check to see if args are valid
    type = ARG1(argv[1]);
    checkchar(argv[2]);
    checkchar(argv[3]);
//strips white space and makes lowercase
    strcpy(Input,stripwhite(argv[2]));
    strcpy(Code,stripwhite(argv[3]));
//check type and pick encode or decode
    if(type==1){
        strcpy(Output,Encode(Input,Code));
        printf("\nYour Code is : %s\n",Output);
    }else{
        strcpy(Output,Decode(Input,Code));
        printf("\nYour Message is : %s\n",Output);
    }
}