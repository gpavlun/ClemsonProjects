#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
name:       Gregory Pavlunenko
user:       gpavlun
course:     ECE2220
semester:   fall
project:    5
purpose:    This project is designed to replicate the word game "ZEN WORD".
            It will read a dictionary and generate a list of letters, then
            find up to 40 words with those letters and allow the user to
            guess them.
assump.:    This code assumes a txt file with each line of that file being
            a single word.
bugs:       none I know of
notes:      This code is a bit of a beast, some things could have been done
            more effeciently, but with the time I had this was the best I
            could do. The game is fully functional though.      
*/
/*
function:   SortWords
purpose:    Sorts all of the given words by length
inputs:     Pointer to array of strings
output:     none
*/
void SortWords(char Words[40][20]){
    char Temp[40][20];
    
    int i,j,k;
    k = 0;
    for(i=0;i<40;i++){
        strcpy(Temp[i],"");

    }
    for(i=0;i<40;i++){
        //("%s",Words[i]);
    }
    for(i=3;i<7;i++){
        for(j=0;j<39;j++){
            if(strlen(Words[j])==(i+1)){
                strcpy(Temp[k],Words[j]);
                k++;
            }
        }
    }
    for(i=0;i<40;i++){
        strcpy(Words[i],Temp[i]);
    }
}
/*
function:   FindLetters
purpose:    Finds a set of letters that are reasonable 
            to form a word
inputs:     Pointer to array of numbers, each representing
            a letter
output:     none
*/
void FindLetters(int *value){
    int i;
    int j;
    int con = 0;
    int vowels = 0;
    int uncommon = 0;
    while(con==0){
        for(i=0;i<7;i++){
            value[i] = 0;
            while(value[i]==0){
    
                value[i] = rand() % (27);
    
                for(j=0;j<7;j++){
    
                    if ((value[i]==value[j])&&i!=j){
    
                        value[i]=0;
    
                    }
                }
            }
        }
        for(i=0;i<7;i++){
            if(value[i]==1||value[i]==5||value[i]==9||value[i]==15||value[i]==21){
                vowels++;
            }
        }
        if(vowels<2){
            con = 0;
            vowels = 0;
        }else{
            for(i=0;i<7;i++){
                if(value[i]==10||value[i]==17||value[i]==26){
                    uncommon++;
                }
            }
            if(uncommon>2){
                con = 0;
                uncommon = 0;
            }else{
                con = 1;
            }
        }
    }
}
/*
function:   Display
purpose:    Accepts user input
inputs:     test - tells which state game is in
output:     the user input as a string
*/
char *Display(int test){
    static char UserInput[8];
    if((test!=-1)&&(test!=-2)){
        printf("Please type a word: ");
    }else if(test!=-2){
        printf("XXX Not a word, try again: ");
    }else{
        printf("You got all the words! Enter Q to quit or anything else to play again");
    }
    
    fgets(UserInput,8,stdin);

    if(UserInput[strlen(UserInput)-1] != '\n'){
        int ch = 0;
        while((ch = getchar()) != '\n' && ch != EOF);
    }
    for(int i=0;i<strlen(UserInput);i++){
        UserInput[i]=toupper(UserInput[i]);
    }
    return UserInput;
}
/*
function:   compare
purpose:    Checks to see if the userinput is a 
            valid word.
inputs:     pointer to Userinput and to the array of 
            chosen words
output:     returns index of word array that contains 
            the matching value, -1 if not found
*/
int compare(char* UserInput, char WordBlock[40][20]){
    int i;
    char temp[20];

    
    for(i=0;i<40;i++){

        if(strlen(WordBlock[i])==5){
            sprintf(temp, "%.3s\n",WordBlock[i]);
        }else if(strlen(WordBlock[i])==6){
            sprintf(temp, "%.4s\n",WordBlock[i]);
        }else if(strlen(WordBlock[i])==7){
            sprintf(temp, "%.5s\n",WordBlock[i]);
        }else if(strlen(WordBlock[i])==8){
            sprintf(temp, "%.6s\n",WordBlock[i]);
        }else if(strlen(WordBlock[i])==9){
            sprintf(temp, "%.7s\n",WordBlock[i]);
        }


        if(strcmp(UserInput,temp)==0){
            return i;
            
            
        }
    }
    return -1;
}
/*
function:   WordPrint
purpose:    This is a big gross print statement that
            was designe to make the exact terminal
            print out that the directions wanted. there
            is probably a more elegant way to do this,
            but I was running out of time and this was
            easiest.
inputs:     Number of rows, pointers to the chosen words
            and to an array of the completed words.
output:     none
*/
void WordPrint(int rows,char Wordblock[40][20],int FoundValue[40]){
    
    int i=0;
    for(i=0;i<(rows);i++){
        if(strlen(Wordblock[i])==5){
            ///printf("%d",FoundValue[i]);
            if(FoundValue[i]==0){
                printf("|%.1s--     ",Wordblock[i]);
            }else{
                printf("|%.3s     ",Wordblock[i]);
            }
        }else if(strlen(Wordblock[i])==6){
            if(FoundValue[i]==0){
                printf("|%.1s---    ",Wordblock[i]);
            }else{
                printf("|%.4s    ",Wordblock[i]);
            }
        }else if(strlen(Wordblock[i])==7){
            if(FoundValue[i]==0){
                printf("|%.1s----   ",Wordblock[i]);
            }else{
                printf("|%.5s   ",Wordblock[i]);
            }
        }else if(strlen(Wordblock[i])==8){
            if(FoundValue[i]==0){
                printf("|%.1s-----  ",Wordblock[i]);
            }else{
                printf("|%.6s  ",Wordblock[i]);
            }
        }else if(strlen(Wordblock[i])==9){
            if(FoundValue[i]==0){
                printf("|%.1s------ ",Wordblock[i]);
            }else{
                printf("|%.7s ",Wordblock[i]);
            }
        }else if(strlen(Wordblock[i])==0){
            printf("|        |");
        }

        if(strlen(Wordblock[i+rows])==5){
            if(FoundValue[i+rows]==0){
                printf("|%.1s--     ",Wordblock[i+rows]);
            }else{
                printf("|%.3s     ",Wordblock[i+rows]);
            }
        }else if(strlen(Wordblock[i+rows])==6){
            if(FoundValue[i+rows]==0){
                printf("|%.1s---    ",Wordblock[i+rows]);
            }else{
                printf("|%.4s    ",Wordblock[i+rows]);
            }
        }else if(strlen(Wordblock[i+rows])==7){
            if(FoundValue[i+rows]==0){
                printf("|%.1s----   ",Wordblock[i+rows]);
            }else{
                printf("|%.5s   ",Wordblock[i+rows]);
            }
        }else if(strlen(Wordblock[i+rows])==8){
            if(FoundValue[i+rows]==0){
                printf("|%.1s-----  ",Wordblock[i+rows]);
            }else{
                printf("|%.6s  ",Wordblock[i+rows]);
            }
        }else if(strlen(Wordblock[i+rows])==9){
            if(FoundValue[i+rows]==0){
                printf("|%.1s------ ",Wordblock[i+rows]);
            }else{
                printf("|%.7s ",Wordblock[i+rows]);
            }
        }else if(strlen(Wordblock[i+rows])==0){
            printf("|        |");
        }

        if(strlen(Wordblock[i+rows*2])==5){
            if(FoundValue[i+rows*2]==0){
                printf("|%.1s--     ",Wordblock[i+rows*2]);
            }else{
                printf("|%.3s     ",Wordblock[i+rows*2]);
            }
        }else if(strlen(Wordblock[i+rows*2])==6){
            if(FoundValue[i+rows*2]==0){
                printf("|%.1s---    ",Wordblock[i+rows*2]);
            }else{
                printf("|%.4s    ",Wordblock[i+rows*2]);
            }
        }else if(strlen(Wordblock[i+rows*2])==7){
            if(FoundValue[i+rows*2]==0){
                printf("|%.1s----   ",Wordblock[i+rows*2]);
            }else{
                printf("|%.5s   ",Wordblock[i+rows*2]);
            }
        }else if(strlen(Wordblock[i+rows*2])==8){
            if(FoundValue[i+rows*2]==0){
                printf("|%.1s-----  ",Wordblock[i+rows*2]);
            }else{
                printf("|%.6s  ",Wordblock[i+rows*2]);
            }
        }else if(strlen(Wordblock[i+rows*2])==9){
            if(FoundValue[i+rows*2]==0){
                printf("|%.1s------ ",Wordblock[i+rows*2]);
            }else{
                printf("|%.7s ",Wordblock[i+rows*2]);
            }
        }else if(strlen(Wordblock[i+rows*2])==0){
            printf("|        |");
        }

        if(strlen(Wordblock[i+rows*3])==5){
            if(FoundValue[i+rows*3]==0){
                printf("|%.1s--     |",Wordblock[i+rows*3]);
            }else{
                printf("|%.3s     |",Wordblock[i+rows*3]);
            }
        }else if(strlen(Wordblock[i+rows*3])==6){
            if(FoundValue[i+rows*3]==0){
                printf("|%.1s---    |",Wordblock[i+rows*3]);
            }else{
                printf("|%.4s    |",Wordblock[i+rows*3]);
            }
        }else if(strlen(Wordblock[i+rows*3])==7){
            if(FoundValue[i+rows*3]==0){
                printf("|%.1s----   |",Wordblock[i+rows*3]);
            }else{
                printf("|%.5s   |",Wordblock[i+rows*3]);
            }
        }else if(strlen(Wordblock[i+rows*3])==8){
            if(FoundValue[i+rows*3]==0){
                printf("|%.1s-----  |",Wordblock[i+rows*3]);
            }else{
                printf("|%.6s  |",Wordblock[i+rows*3]);
            }
        }else if(strlen(Wordblock[i+rows*3])==9){
            if(FoundValue[i+rows*3]==0){
                printf("|%.1s------ |",Wordblock[i+rows*3]);
            }else{
                printf("|%.7s |",Wordblock[i+rows*3]);
            }
        }else if(strlen(Wordblock[i+rows*3])==0){
            printf("|        |");
        }
        printf("\n");
    }
}
/*
function:   BullshitCeilingFuncBecauseMathhIsntWorking
purpose:    I don't want to talk about it. literally
            just the math.h ceil() function.
inputs:     value
output:     ceiling of value/4
*/
int BullshitCeilingFuncBecauseMathhIsntWorking(int counter0){
    float counter1 = (float)counter0;
    counter0 = counter0/4;
    counter1 = counter1/4;
    int rows;
    if(counter1!=counter0){
        rows = counter0+1;
    }else{
        rows = counter0;
    }
    return rows;
}
/*
function:   FilterWords
purpose:    This function checks through the dictionary
            and only takes in the words that can be 
            made with the letter combination chosen.
inputs:     pointer to the chosen words array, all words
            array, the array of chosen letters, and the
            number of lines in the file.
output:     none
*/
void FilterWords(char Wordblock[40][20],char **pMatrix,int value[7],double lines){
    int con = 0;
    int counter0 = 0;
    int i = 0;
    int k = 0;
    int l = 0;
    int j = 0;
    for(i=0;i<lines;i++){
            
        if((strlen((*(pMatrix+i)))<10)&&(strlen((*(pMatrix+i)))>4)){
            con = 1;
            for(k=0;k<7;k++){
                counter0 = 0;
                
                for(j=0;j<strlen((*(pMatrix+i)));j++){
                    if(((*(pMatrix+i))[j]!=(value[0])+64)&&((*(pMatrix+i))[j]!=(value[1])+64)&&((*(pMatrix+i))[j]!=(value[2])+64)
                    &&((*(pMatrix+i))[j]!=(value[3])+64)&&((*(pMatrix+i))[j]!=(value[4])+64)&&((*(pMatrix+i))[j]!=(value[5])+64)
                    &&((*(pMatrix+i))[j]!=(value[6])+64)&&((*(pMatrix+i))[j]!=0)&&((*(pMatrix+i))[j]!=10)&&((*(pMatrix+i))[j]!=12)&&((*(pMatrix+i))[j]!=13)){
                        con = 0;
                    }
                    if(((*(pMatrix+i))[j]==(value[k])+64)){
                        counter0++;

                    }
                }
                if(counter0>1){
                    con = 0;
                }
            }
            if((con==1)){
                
                strcpy(Wordblock[l],(*(pMatrix+i)));

                l++;
            }
        }
        if(l==41){
            i = lines;
        }
            
    }
}

int main(int argc, char* argv[]){

    /*
    Loops unil "Q" is entered. It will read the words from the dictionary everytime, 
    if it takes long enough you will see the dots appear. Then it clears the screen
    and generates the game. Most of main is just allocating the space needed to
    store all the values.
    */
   int i;//iteration value
   int j;//iteration value
   int con;//looping value
   int Check;//looping value
   long int END;//end of file address
   double lines;//number of lines
   char c;//temporary value
   int counter0;//counter
   char **pMatrix;//pointer to array of pointers
   char *pWords;//pointer to array of words
   int value[7];//array of letters or game
   char UserInput[10];//String for user input
   int FoundValue[40] = {0};//array representing found words
   int test;//intermediate value

    while(1==1){
        system("clear");
        i = 0;
        j = 0;
        con = 0;
        Check = 0;
        counter0 = 0;
        test = 0;

        

        FILE* pDictionary;
        /*open the dictionary and see how big it is*/
        pDictionary = fopen(argv[1],"r");
        fseek(pDictionary, 0L, SEEK_END);
        END = ftell(pDictionary);

        fseek(pDictionary, 0L, SEEK_SET);
        lines = 0;
        
        while(ftell(pDictionary)!=END){
            fread(&c, 1, 1, pDictionary);
            if(c=='\n'){
                lines++;
            }
        }
        fseek(pDictionary, 0L, SEEK_SET);

        /*allocate space for the words in the dictionary*/
        pMatrix = (char **)malloc(lines*(sizeof(char *)));
        pWords = (char *)malloc(lines*20);

        /*reads in all the words*/
        printf("Begin reading words\n");
        printf("Reading");

        for(i=0;i<lines;i++){
            *(pMatrix+i) = (pWords + i*20);
            c = 0;
            j = 0;
            while(c!='\n'){
                fread(&c, 1, 1, pDictionary);
                *((*(pMatrix+i)) + j)= toupper(c);
                j++;
            }
            *((*(pMatrix+i)) + j)= '\0';
            counter0++;
            if(counter0==10000){
                printf(".");
                fflush(stdout);
                counter0 = 0;
            }
        }
        printf("\nFinished reading words\n\n");
        
        fclose(pDictionary);
        /*generates letter combo*/

        FindLetters(value);
        /*creates a blank block of mem for words*/
        char Wordblock[40][20];
        for(i=0;i<40;i++){
            strcpy(Wordblock[i],"");
        }
        /*choose words from the dictionary to be used*/
        FilterWords(Wordblock,pMatrix,value,lines);
        /*converts the letter combos to their ascii values*/
        for(i=0;i<7;i++){
            value[i] = value[i]+64;
        }
        
        free(pMatrix);
        free(pWords);
        
    
        /*creates a zero-ed out block of memory, used to
        know it the word is completed or not*/
        for(i=0;i<40;i++){
            if(strlen(Wordblock[i])==0){
                FoundValue[i] = 1;
            }else{
                FoundValue[i] = 0;
            }
        }


        /*sort all the words by length*/
        SortWords(Wordblock);
        
        while(Check==0){
            /*creates the game board*/
            system("clear");
            printf("\n\t          %c     \n",value[0]);
            printf("\t       %c     %c   \n",value[1],value[2]);
            printf("\t      %c       %c  \n",value[3],value[4]);
            printf("\t        %c   %c   \n\n\n",value[5],value[6]);
            
            
            /*checks to see how many of the 40 possible 
            words were used*/
            counter0 = 0;
            for(i=0;i<40;i++){
                if(strcmp(Wordblock[i],"")!=0){
                    counter0++;
                }
            }
            /*calculated number of rows needed for 4 columns*/
            int rows = BullshitCeilingFuncBecauseMathhIsntWorking(counter0);
            /*displays all words in requested format*/
            WordPrint(rows,Wordblock,FoundValue);

            /*win condition, checks to see if all words are found*/
            con = 1;
            for(i=0;i<40;i++){ 
                if(FoundValue[i]==0){
                    con = 0;
                }
            }
            /*if all words found, ends loop and makes new game,
            otherwise is will prompt for next input with response
            to previous*/
            if(con == 1){
                test = -2;
                strcpy(UserInput,Display(test));
                if(strcmp(UserInput,"Q\n")==0){
                    exit(0);
                }else{
                    Check = 1;
                }
            }else{
                strcpy(UserInput,Display(test));
                if(strcmp(UserInput,"Q\n")==0){
                    exit(0);
                }

                test = compare(UserInput,Wordblock);
        
                if(test!=-1){
                    FoundValue[test]=1;
                }
            }
        }
    }

    return 0;
}