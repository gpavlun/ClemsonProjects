/*
name:     Gregory Pavlunenko
user:     gpavlun
course:   ECE2220
semester: fall
project:  3
purpose: encodes or decodes strings of characters using hamming Code
assumptions: I am assuming that the person using this has some basic understanding of ASCII values
bugs: none that I know of, but that doesn't mean there aren't any
notes: I know this kind of looks like shit, I tried to comment it as well as I could
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
function: string to binary (stb)
purpose: takes a string of binary values and converts
         them to an int type
*/
int stb(char UserInput[]){
    int binary[4] = {0,0,0,0};/*stores the binary digits*/
    int i,j,k;/*iteration variables*/
    int ret = 0;/*return value*/
    /*this is basically and exponent function,
    the one in math.h wasn't very good so 
    I made my own*/
    for(i=3,j=0;i>=0;i--,j++){
    
        if(UserInput[i]-'0'==1){
    
            if(j==0){
    
                binary[i] = 1;
    
            }else if(j==1){
    
                binary[i] = 2;
    
            }else{
    
                binary[i] = 2;
    
                for(k=0;k<j-1;k++){
    
                    binary[i]=binary[i]*2;
    
                }
            }  
        }
    }
    for(i=0;i<4;i++){
        ret = ret + binary[i];
    }
    return ret;
}
/*
function: integer to binary (itb)
purpose: takes an integer value and converts
         it into binary, returned as a string
*/
char *itb(int n,int d){ 
    static char ret[50] = "";/*string that will hold the binary value*/
    int binary[d]; /*array that stores the binary value*/
    strcpy(ret,"");/*half assed attempt to clear the string just in case*/
    int i,j,k;/*iteration values*/
    char squigg[5];/*random temp variable to transition between to variables*/
    /*super basic, takes the modulo of
    the number and loads it into an array
    representing a binary number, then
    prints it into a string*/
    for(i=0;i<d;i++){
    
        binary[i] = 0;
    
    }
    i = 0;
    while (n>0){ 
    
        binary[i] = n % 2; 
        n = n / 2; 
        i++; 
    
    } 
    for (j=(d-1),k=0;j>=0;j--,k++){
    
        sprintf(squigg,"%d",binary[j]);
        ret[k] = squigg[0];
    
    }

    return ret;
} 
/*
function: Input
purpose: reads user input and decides whether or not it is viable for the rest of the functions
*/
char *Input(char Encode[],char Decode[], char Quit[]){
    while(1){
        static char UserInput[16] = "";/*User Input*/
        int Pass = 0;/*determines if the input was valid*/
        int Check[3][7];/*check values for various criteria*/
        int n = 0;/*iteration variable*/

        while(Pass==0){

            fgets(UserInput,16,stdin);

            if(UserInput[strlen(UserInput)-1] != '\n'){
            
                int ch = 0;
                while((ch = getchar()) != '\n' && ch != EOF);
            
            }
            if(strcmp(UserInput,Quit)==0){
            
                exit(0);
            }
            /*checks to see if the string entered is "encode" or "decode"*/
            Pass = 1;
            
            for(n=0;n<strlen(Encode);n++){
            
                Check[0][n] = UserInput[n]-Encode[n];
                Check[1][n] = UserInput[n]-Decode[n];
            
            }
            for(n=0;n<strlen(Quit);n++){
            
                Check[2][n] = UserInput[n]-Quit[n];
            
            }
            for(n=0;n<strlen(Encode);n++){
                
                if(Check[0][n]!=0){
                
                    if(Check[1][n]!=0){
                
                        Pass = 0;
                
                    }else{
                
                        Pass = 2;
                    }
                }  
            }
            /*0 means neither, 1 is encode, 2 is decode*/
            if(Pass==0){

                printf("Please type \"encode\" or \"decode\" followed by a space\n");

            }
            if(Pass==1){

                if(((UserInput[7]<33||UserInput[7]>126)||(UserInput[8]<33||UserInput[8]>126))||strlen(UserInput)>10){
                    
                    printf("Follow \"encode\" with a space and two printable ASCII characters(33-126)\n");
                    Pass=0;
                
                }else{
                    
                    return UserInput;
                
                }
            }
            if(Pass==2){

                for(n=0;n<6;n++){

                    if(((UserInput[7+n]<'0'||UserInput[7+n]>'9')&&(UserInput[7+n]<'A'||UserInput[7+n]>'F'))){
                        
                        Pass = 0;
                    }          
                }
                if(strlen(UserInput)!=14){

                    Pass = 0;

                }
                if(Pass==2){

                    return UserInput;

                }
                if(Pass==0){

                    printf("Follow \"decode\" with a space and six hex digits(0123456789 ABCDEF)\n");
                }
            }
        }
    }
}
/*
function: encode
purpose: encodes the user input via Hamming
*/
void encode(char UserInput[]){
    /*this whole thing is eye cancer so let me explain it.
    Basically, I encoded the entire value with a single line of code
    moreso out of spite for this stupid project than anything, but 
    also because it said "use bitwise operators", so I used only
    bitwise operators to encode it. All it actually does is shift and
    add bits together. I did it all in hex just because it is 
    easier to think in hex for me*/
    int A = UserInput[7];/*first half of the string*/
    int B = UserInput[8];/*second half of the string*/
    int C;/*combined into one*/
    int D;/*encoded value*/
    
    C = (B<<8)+A;
    /*every other term of the operation is information, the inbetween terms are parity bits*/
    D = ((C&0xF800)*0x20)  +  ((((C&0x8000)>>15)^((C&0x4000)>>14)^((C&0x2000)>>13)^((C&0x1000)>>12)^((C&0x0800)>>11))*0x8000)
      +  ((C&0x07F0)*0x10)  +  ((((C&0x400)>>10)^((C&0x200)>>9)^((C&0x100)>>8)^((C&0x80)>>7)^((C&0x40)>>6)^((C&0x20)>>5)^((C&0x10)>>4))*0x80)
      +  ((C&0x000E)<<3)  +  ((((C&0x8000)>>15)^((C&0x4000)>>14)^((C&0x400)>>10)^((C&0x200)>>9)^((C&0x100)>>8)^((C&0x80)>>7)^((C&0x8)>>3)^((C&0x4)>>2)^((C&0x2)>>1))*0x8)  + ((C&0x0001)<<2)  
      +  ((((C&0x2000)>>13)^((C&0x1000)>>12)^((C&0x400)>>10)^((C&0x200)>>9)^((C&0x40)>>6)^((C&0x20)>>5)^((C&0x8)>>3)^((C&0x4)>>2)^((C&0x1)))*0x2)  
      +  (((C&0x8000)>>15)^((C&0x2000)>>13)^((C&0x800)>>11)^((C&0x400)>>10)^((C&0x100)>>8)^((C&0x40)>>6)^((C&0x10)>>4)^((C&0x8)>>3)^((C&0x2)>>1)^(C&0x1));
    system("clear");
    printf("your value: %c%c\n",A,B);
    printf("                \n");
    printf(" %c :0x%X , %s  \n",B,B,itb(B,8));
    printf(" %c :0x%X , %s  \n",A,A,itb(A,8));
    printf(" 0x%X%X  , %s%s\n\n",B,A,itb(B,8),itb(B,8));
    printf("your parity bits are: 16->[%d] 8->[%d] 4->[%d] 2->[%d] 1->[%d]\n",((((C&0x8000)>>15)^((C&0x4000)>>14)^((C&0x2000)>>13)^((C&0x1000)>>12)^((C&0x0800)>>11))),
                                                                              ((((C&0x400)>>10)^((C&0x200)>>9)^((C&0x100)>>8)^((C&0x80)>>7)^((C&0x40)>>6)^((C&0x20)>>5)^((C&0x10)>>4))),
                                                                              ((((C&0x8000)>>15)^((C&0x4000)>>14)^((C&0x400)>>10)^((C&0x200)>>9)^((C&0x100)>>8)^((C&0x80)>>7)^((C&0x8)>>3)^((C&0x4)>>2)^((C&0x2)>>1))),
                                                                              ((((C&0x2000)>>13)^((C&0x1000)>>12)^((C&0x400)>>10)^((C&0x200)>>9)^((C&0x40)>>6)^((C&0x20)>>5)^((C&0x8)>>3)^((C&0x4)>>2)^((C&0x1)))),
                                                                              (((C&0x8000)>>15)^((C&0x2000)>>13)^((C&0x800)>>11)^((C&0x400)>>10)^((C&0x100)>>8)^((C&0x40)>>6)^((C&0x10)>>4)^((C&0x8)>>3)^((C&0x2)>>1)^(C&0x1)));
    printf("output:\n hexadecimal | %06X\n binary      | %s\n\n\n\n\n",D,itb(D,21));
}
/*
function: decode
purpose: deocodes the user input via Hamming
*/
void decode(char UserInput[]){
    int code[6];/*the user input stored in an array*/
    int value;/*the user input converted to an int*/
    char strvalue[30];/*the value stored in binary*/
    char cone[10];/*each of these are individual nibbles*/
    char ctwo[10];
    char cthree[10];
    char cfour[10];
    /*super basic, converts ascii string into
    the hex values that they look like*/
    system("clear");

    for(int i=7,j=0;i<13;i++,j++){

        if(UserInput[i] == 'A'){
            code[j] = 0xA;
        }else if(UserInput[i] == 'B'){
            code[j] = 0xB;
        }else if(UserInput[i] == 'C'){
            code[j] = 0xC;
        }else if(UserInput[i] == 'D'){
            code[j] = 0xD;
        }else if(UserInput[i] == 'E'){
            code[j] = 0xE;
        }else if(UserInput[i] == 'F'){
            code[j] = 0xF;
        }else if(UserInput[i] == '1'){
            code[j] = 0x1;
        }else if(UserInput[i] == '2'){
            code[j] = 0x2;
        }else if(UserInput[i] == '3'){
            code[j] = 0x3;
        }else if(UserInput[i] == '4'){
            code[j] = 0x4;
        }else if(UserInput[i] == '5'){
            code[j] = 0x5;
        }else if(UserInput[i] == '6'){
            code[j] = 0x6;
        }else if(UserInput[i] == '7'){
            code[j] = 0x7;
        }else if(UserInput[i] == '8'){
            code[j] = 0x8;
        }else if(UserInput[i] == '9'){
            code[j] = 0x9;
        }else if(UserInput[i] == '0'){
            code[j] = 0x0;
        }
    }
    /*storing the values of the array into an int*/
    value = (code[0]*0x100000)+(code[1]*0x10000)+(code[2]*0x1000)+(code[3]*0x100)+(code[4]*0x10)+(code[5]);
    strcpy(strvalue,itb(value,21));/*converting the value into a binary string*/
    printf("%X\n",value);
    printf("the binary code is:\n");
    printf("---%s\n",strvalue);
    printf("   ^^^^^ ^^^^^^^ ^^^ ^\n");
    sprintf(cfour,"%c%c%c%c",strvalue[0],strvalue[1],strvalue[2],strvalue[3]);
    sprintf(cthree,"%c%c%c%c",strvalue[4],strvalue[6],strvalue[7],strvalue[8]);
    sprintf(ctwo,"%c%c%c%c",strvalue[9],strvalue[10],strvalue[11],strvalue[12]);
    sprintf(cone,"%c%c%c%c",strvalue[14],strvalue[15],strvalue[16],strvalue[18]);
    printf("b: %s %s %s %s\n",cfour,cthree,ctwo,cone);
    printf("h: 0x%X  0x%X  0x%X  0x%X\n",stb(cfour),stb(cthree),stb(ctwo),stb(cone));
    printf("     \"%c\"       \"%c\" \n",(stb(cfour)*0x10)+stb(cthree),(stb(ctwo)*0x10)+stb(cone));
    printf("Information Word : %c%c\n\n",(stb(ctwo)*0x10)+stb(cone),(stb(cfour)*0x10)+stb(cthree));
}

int main(){
    /*all main does is call functions and print the original prompt*/
    char UserInput[16] = "";/*all variables are templates sent to the functions*/
    char Encode[] = "encode ";
    char Decode[] = "decode ";
    char Quit[] = "quit\n";
    //int Check[2][7];
    //int Pass = 0;
    //int n = 0;
    while(1){
        
        printf("Please type \"encode\" along with two printable ASCII characters,\n");
        printf("or type \"decode\" along with six hex digits. Please include a space\n");
        printf("between \"encode\" or \"decode\" and the following characters.\n\n");
        printf("Alternatively, type \"quit\" to quit.\n");
        strcpy(UserInput,Input(Encode,Decode,Quit));

        if(UserInput[0]=='e'){

            encode(UserInput);

        }else{

            decode(UserInput);

        }
    }
    return 0;
}