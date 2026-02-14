/*
name:     Gregory Pavlunenko
user:     gpavlun
course:   ECE2220
semester: fall
project:  1
purpose: this code is designed to allow the user to play bingo,
here called "tiger", by randomly generating a gameboard and 
calling numbers from it. there are few assumptions here, other 
than assuming the user has an enter and q key. and that they 
want to play bingo. I do not know of any bugs with this.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
    /*conditional variables*/
    int randomvalue = 0;
    int row = 0;
    int col = 0;
    char letter = 0;
    int colvalue= 0;
    int gamenumber = 0;
    /*temporary variables*/
    int ceiling = 0;
    int floor = 0;
    char string[10] = "";
    char userinput[5] = "";
    /*iteration variables*/
    int r = 0;
    int c = 0;
    int u = 0;
    int i = 0;
    int h = 0;
    int continue0 = 0;
    int continue1 = 0;

    while(0==0){
    
        continue0 = 0;
        /*gameboard*/
        int board[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};/*original generated values stored here*/
        int squarestate[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,1,0,0},{0,0,0,0,0},{0,0,0,0,0}};/*squares which have already been picked*/
        char stringboard[25][3] = {"00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00"};/*string version of the board*/
        int flatboard[1][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};/*flattened version of the matrix*/
        int occurances = 0;/*stores how many times a letter number combination has been chosen*/
        char prints[25][16];//stores all generated letter combinations for reprint
        char str[20] = "";
        


        /*this nest loop generates 25 unique
        random numbers and assigns them to
        the squares on the board*/

        for(c=0;c<5;c++){

            for(r=0;r<5;r++){

                u = 0;

                while(u==0){

                    u = 1;
                    ceiling = ((c + 1) * 20) + 1;
                    floor = ((c + 1) * 20) - 20;
                    randomvalue = rand() % (ceiling - floor) + floor;

                    for(i=0;i<5;i++){

                        if(randomvalue==board[i][c]||randomvalue==100){

                            u = 0;
                        }
                    }
                }      

                board[r][c] = randomvalue;
            }
        }

        r = 0;
        c = 0;
        
        /*this loop makes up the bulk of the program,
        it is the code to pick random values on the
        board and generate the ui*/

        while(continue0==0){

            i = 0;

            /*this loop takes the matrix and flattens it
            into a vector, if the conditional board(squarestate) has
            a 1 in it, that indicates a place has already
            been called and so the vector will not
            include it*/

            for(c=0;c<5;c++){

                for(r=0;r<5;r++){

                    if(squarestate[r][c]==1){

                        flatboard[0][i] = 0;

                    }else{

                        flatboard[0][i] = board[r][c];
                    }

                    i++;
                }
            }

            /*this loop will take the vector flatboard and
            convert the decimal digits into strings
            for the purpose of creating the graphic.
            if a 0 is in the vector, an XX will be 
            placed in that spot*/

            for(int l=0;l<25;l++){

                if(flatboard[0][l]>=10){

                    sprintf(string,"%d",flatboard[0][l]);
                }
                if(flatboard[0][l]<10&&flatboard[0][l]>0){

                    sprintf(string,"0%d",flatboard[0][l]);
                }
                if(flatboard[0][l]==0){

                    sprintf(string,"XX");
                }
                strcpy(stringboard[l],string);
            }

            /*this the board, it takes the string
            array and places the strings where they
            are needed on the board*/

            system("clear"); 
            printf("\n   T      I      G      E      R    \n");
            printf("------------------------------------\n");
            printf("|  %s  |  %s  |  %s  |  %s  |  %s  |\n",stringboard[0],stringboard[5],stringboard[10],stringboard[15],stringboard[20]);
            printf("|------|------|------|------|------|\n");
            printf("|  %s  |  %s  |  %s  |  %s  |  %s  |\n",stringboard[1],stringboard[6],stringboard[11],stringboard[16],stringboard[21]);
            printf("|------|------|------|------|------|\n");
            printf("|  %s  |  %s  | FREE |  %s  |  %s  |\n",stringboard[2],stringboard[7],                stringboard[17],stringboard[22]);
            printf("|------|------|------|------|------|\n");
            printf("|  %s  |  %s  |  %s  |  %s  |  %s  |\n",stringboard[3],stringboard[8],stringboard[13],stringboard[18],stringboard[23]);
            printf("|------|------|------|------|------|\n");
            printf("|  %s  |  %s  |  %s  |  %s  |  %s  |\n",stringboard[4],stringboard[9],stringboard[14],stringboard[19],stringboard[24]);
            printf("------------------------------------\n");
            printf("press \"ENTER\" to generate a square (or enter \"q\" to quit): ");
            
            for(int j=0; j<(occurances);j++){

                printf("\n%s",prints[j]);
            
            }
            

            u = 0;

            /*checks for tiger in rows*/

            for(r=0;r<5;r++){

                h = 1;
                
                for(c=0;c<5;c++){
                
                    if(squarestate[r][c]==0){
                
                        h = 0;
                
                    }
                }
                
                if(h==1){
                
                    u = 1;
                    continue0 = 1;
                
                }
            }

            /*checks for tiger in columns*/

            for(c=0;c<5;c++){

                h = 1;
                
                for(r=0;r<5;r++){
                
                    if(squarestate[r][c]==0){
                
                        h = 0;
                
                    }
                }
                
                if(h==1){
                
                    u = 1;
                    continue0 = 1;
                }
            }

            /*checks for tiger on diagonals*/

            if(squarestate[0][0]==1&&squarestate[1][1]==1&&squarestate[2][2]==1&&squarestate[3][3]==1&&squarestate[4][4]==1){

                u = 1;
                continue0 = 1;

            }

            if(squarestate[0][4]==1&&squarestate[1][3]==1&&squarestate[2][2]==1&&squarestate[3][1]==1&&squarestate[4][0]==1){

                u = 1;
                continue0 = 1;

            }

            /*this loop is input verification, if
            the given input is not viable it will
            not let you continue until it is.
            it will teminate the program if q is
            entered*/

            while(u==0){

                printf("\n");
                fgets(userinput, 5, stdin);

                if(strcmp(userinput,"q\n")==0){

                    exit(0);

                }else if(strcmp(userinput,"\n")==0){

                    u = 1; 

                }else{

                    printf("type q or enter: ");

                }
            }

            /*this keeps track of each time a square is called*/

            if(continue0==0){

                continue1 = 0;

                while(continue1==0){

                    continue1 = 1;
                    col = rand() % (5);
                    row = rand() % (5); 

                    if(squarestate[row][col]==1){

                        continue1 = 0;

                    }
            }
              
            squarestate[row][col] = 1;
            occurances++;
            if(col==0){

                letter = 84;

            }else if(col==1){

                letter = 73;

            }else if(col==2){

                letter = 71;

            }else if(col==3){

                letter = 69;

            }else if(col==4){

                letter = 82;

            }

            colvalue = board[row][col];
            sprintf(str,"%d : %c - %d",occurances,letter,colvalue);
            strcpy(prints[occurances-1],str);

            }
        }
        
        /*past this point, the code will
        make checks to see if you want
        to play again, in which case it
        will loop back to the beginning,
        otherwise it will terminate*/

        printf("\nyou got tiger! it took %d turns\n",occurances);
        gamenumber++;
        printf("enter \"q\" to quit or anything else to play again!");
        fgets(userinput, 5, stdin);

        if(strcmp(userinput,"q\n")==0){

            printf("you played %d games!\n",gamenumber);
            exit(0);
        }
    }
    return 0;
}
