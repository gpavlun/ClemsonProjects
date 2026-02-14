/*
name:     Gregory Pavlunenko
user:     gpavlun
course:   ECE2220
semester: fall
project:  2
purpose: lets you enter a football player's data
assumptions: person does not have multiple middle names, theyre phone number is exactly 10 digits
bugs: i dont know if you would consider it a bug, but you cannot exit out of an option once you select it.
      you can put any combo of letters in for Class. It said etc. on the document so i assume you can put whatever.
      if the player made exactly 1/10 of a cent of money, it will be read as an unkown value.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
function: Display
purpose: this function shows the display and lets you select an option
*/
char *Display(void){
    static char UserInput[3];
    int Continue = 0;
    system("clear");
    printf("|         Enter Data         |         Options         |\n");
    printf("|----------------------------|-------------------------|\n");
    printf("|(1) Name                    |(6) Display Data         |\n");
    printf("|(2) School Information      |(7) Clear Data           |\n");
    printf("|(3) Age, Height, and Weight |(8) Quit                 |\n");
    printf("|(4) Player Information      |                         |\n");
    printf("|(5) Contacts                |                         |\n");
    printf("|----------------------------|-------------------------|\n");
    printf("Please Select an Option, 1 - 8 : ");
    fgets(UserInput,3,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            /*I will only explain this once, as it is basically the same for all functions
            this loop clears the buffer the is filled , the following if statements are 
            input validation to make sure the user input is a valid data type*/
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }
        if(strcmp(UserInput,"1\n")!=0&&strcmp(UserInput,"2\n")!=0&&strcmp(UserInput,"3\n")!=0&&strcmp(UserInput,"4\n")!=0){
            if(strcmp(UserInput,"5\n")!=0&&strcmp(UserInput,"6\n")!=0&&strcmp(UserInput,"7\n")!=0&&strcmp(UserInput,"8\n")!=0){
                printf("Input a Number, 1 - 8 : ");
                fgets(UserInput,3,stdin);
                Continue = 0;
            }
        }
    }
    return UserInput;
}
/*
function: F_Name
purpose: gets the first name
*/
char *F_Name(void){
    static char UserInput[35];
    int Continue = 0;
    system("clear");  
    printf("Please Enter the Player's First Name\n");
    fgets(UserInput,35,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if(strlen(UserInput)>33){
            printf("Max Length 32 Characters\n");
            fgets(UserInput,35,stdin);
            Continue = 0;
        }else if(strlen(UserInput)<2){
            printf("Min Length 1 Character\n");
            fgets(UserInput,35,stdin);
            Continue = 0;
        }
    }
    return UserInput;
}
/*
function: M_Name
purpose: gets the middle initial
*/
char *M_Name(void){
    static char UserInput[5];
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Middle Initial\n");
    fgets(UserInput,5,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if(strlen(UserInput)>2){
            printf("Type One Character\n");
            fgets(UserInput,5,stdin);
            Continue = 0;
        }
    }
    return UserInput;
}
/*
function: L_Name
purpose: gets the last name
*/
char *L_Name(void){
    static char UserInput[35];
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Last Name\n");
    fgets(UserInput,35,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)>33){
            printf("Max Length 32 Characters\n");
            fgets(UserInput,35,stdin);
            Continue = 0;
        }else if(strlen(UserInput)<2){
            printf("Min Length 1 Character\n");
            fgets(UserInput,35,stdin);
            Continue = 0;
        }
    }
    return UserInput;
}
/*
function: School_Info
purpose: collects a string for the school name
*/
char *School_Info(void){
    static char UserInput[67];
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's School\n");
    fgets(UserInput,67,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)>65){
            printf("Max Length 64 Characters\n");
            fgets(UserInput,67,stdin);
            Continue = 0;
        }
        if (strlen(UserInput)<3){
            printf("Min Length 2 Characters\n");
            fgets(UserInput,67,stdin);
            Continue = 0;
        }
    }
    return UserInput;
}
/*
function: Class_Infor
purpose: gets the class value
*/
char *Class_Info(void){
    static char UserInput[6];
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Class\n");
    fgets(UserInput,6,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)>4){
            printf("Max Length 3 Characters\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }
        if (strlen(UserInput)<3){
            printf("Min Length 2 Characters\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }
    }
    return UserInput;
}
/*
function: Age_Num
purpose: accepts user input
*/
int Age_Num(void){
    static char UserInput[5];
    int Age = 0;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Age\n");
    fgets(UserInput,5,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)!=3){
            printf("Please Type 2 Characters\n");
            fgets(UserInput,5,stdin);
            Continue = 0;
        }else{
            Age = atoi(UserInput);
            if(Age>99||Age<21){
                printf("Enter Age From 21 - 99\n");
                fgets(UserInput,5,stdin);
                Continue = 0;
            }
        }
    }
    return Age;
}
/*
function: Height_ft
purpose: gets the foot component of the player height
*/
int Height_ft(void){
    static char UserInput[5];
    int Height;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Feet Component of the Player's Height\n");
    fgets(UserInput,5,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)!=2){
            printf("Please Type 1 Characters\n");
            fgets(UserInput,5,stdin);
            Continue = 0;
        }else{
            Height=atoi(UserInput);
            if(Height>7||Height<4){
                printf("Enter a Number From 4 - 7\n");
                fgets(UserInput,5,stdin);
                Continue = 0;
            }
        }
    }
    return Height;
}
/*
function: Height_in
purpose: gets the inch component of the player height
*/
int Height_in(void){
    char UserInput[5];
    int Height;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Inch Component of the Player's Height\n");
    fgets(UserInput,5,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if(strlen(UserInput)>3){
            printf("Max Length 2 Characters\n");
            fgets(UserInput,5,stdin);
            Continue = 0;
        }else if(strlen(UserInput)<2){
            printf("Min Length 1 Characters\n");
            fgets(UserInput,5,stdin);
            Continue = 0;
        }else if(atoi(UserInput)==0){/*if a 0 is read, it means that either the value is a 0
                                       or not a number,so I make a check here*/
            if(strcmp(UserInput,"0\n")!=0){
                printf("Enter a Number\n");
                fgets(UserInput,5,stdin);
                Continue = 0;
            }
        }else{
            Height=atoi(UserInput);
            if(Height>11||Height<0){
                printf("Enter a Number From 0 - 11\n");
                fgets(UserInput,5,stdin);
                Continue = 0;
            }
        }
    }
    return Height;
}
/*
function: Weight_Num
purpose: gets the integer value of the players weight
*/
int Weight_Num(void){
    char UserInput[8];
    int Weight;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Weight\n");
    fgets(UserInput,8,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        Weight=atoi(UserInput);
        if(Weight>500||Weight<100){
            printf("Weight Must be From 100lb - 500lb\n");
            fgets(UserInput,8,stdin);
            Continue = 0;
        }
    }
    return Weight;
}
/*
function: Position_fn
purpose: gets a string of the player's position
*/
char *Position_fn(void){
    static char UserInput[6];
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Position\n");
    fgets(UserInput,6,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)!=4){
            printf("Type Three Characters\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }else if(isupper(UserInput[0])==0||isupper(UserInput[1])==0||isupper(UserInput[2])==0){
            printf("Type Capital Letters Only\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }
    }
    return UserInput;
}
/*
function: Star_Num
purpose: takes an integer as the star value
*/
int Star_Num(void){
    char UserInput[5];
    int Stars = 0;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Star Rating\n");
    fgets(UserInput,5,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)!=2){
            printf("Please Type 1 Character\n");
            fgets(UserInput,5,stdin);
            Continue = 0;
        }else if(atoi(UserInput)==0){
            if(strcmp(UserInput,"0\n")!=0){
                printf("Enter a Number\n");
                fgets(UserInput,5,stdin);
                Continue = 0;
            }
        }else{
            Stars = atoi(UserInput);
            if(Stars>5||Stars<0){
                printf("Enter Value From 0 - 5\n");
                fgets(UserInput,5,stdin);
                Continue = 0;
            }
        }
    }
    return Stars;
}
/*
function: Money
purpose: gets a floating point value to represent a floating point number
*/
double Money(void){
    char UserInput[55];
    double Money = 0;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's N.I.L. Money\n");
    fgets(UserInput,55,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if(strlen(UserInput)>53){
            printf("Max Length 52 Characters\n");
            fgets(UserInput,55,stdin);
            Continue = 0;
        }else if(strlen(UserInput)<2){
            printf("Min Length 1 Characters\n");
            fgets(UserInput,55,stdin);
            Continue = 0;
        }else if(atof(UserInput)==0){
            if(strcmp(UserInput,"0\n")!=0){
                printf("Enter a Number\n");
                fgets(UserInput,55,stdin);
                Continue = 0;
            }
        }else{
            Money=atof(UserInput);
            if(Money>1.00e+50||Money<0){
                printf("Enter a Number From 0.00 - 1.00x10^50\n");
                fgets(UserInput,55,stdin);
                Continue = 0;
            }
        }
    }
    return Money;
}
/*
function: Twitter
purpose: gets the twitter handle
*/
char *Twitter(void){
    static char UserInput[18];
    int Continue = 0;
    system("clear");
    printf("Please Enter the Player's Twitter Account\n");
    fgets(UserInput,18,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)>16){
            printf("Max Length 15 Characters\n");
            fgets(UserInput,18,stdin);
            Continue = 0;
        }else if(strlen(UserInput)==2){
            printf("Min Length 2 Characters\n");
            fgets(UserInput,18,stdin);
            Continue = 0;
        }else if(strlen(UserInput)>1&&UserInput[0]!='@'){
            printf("Must Start With the \"@\" Symbol");
            fgets(UserInput,18,stdin);
            Continue = 0;
        }else if(strlen(UserInput)==1&&UserInput[0]!='\n'){
            printf("Must Start With the \"@\" Symbol");
            fgets(UserInput,18,stdin);
            Continue = 0;
        }
    }
    return UserInput;
}
/*
function: Phone_1
purpose: gets the first three of a phone number
*/
int Phone_1(void){
    char UserInput[6];
    int Phone = 0;
    int Continue = 0;
    system("clear");
    printf("Please Enter the First 3 Digits of the Player's Phone Number\n");
    fgets(UserInput,6,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)!=4){
            printf("Please Type 3 Characters\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }else if(atoi(UserInput)<100){
            printf("Enter a Number\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }else{
            Phone = atoi(UserInput);
        }
    }
    return Phone;
}
/*
function: Phone_2
purpose: gets the second three of a phone number
*/
int Phone_2(void){
    char UserInput[6];
    int Phone = 0;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Second 3 Digits of the Player's Phone Number\n");
    fgets(UserInput,6,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)!=4){
            printf("Please Type 3 Characters\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }else if(atoi(UserInput)<100){
            printf("Enter a Number\n");
            fgets(UserInput,6,stdin);
            Continue = 0;
        }else{
            Phone = atoi(UserInput);
        }
    }
    return Phone;
}
/*
function: Phone_3
purpose: gets the last four of a phone number
*/
int Phone_3(void){
    char UserInput[7];
    int Phone = 0;
    int Continue = 0;
    system("clear");
    printf("Please Enter the Last 4 Digits of the Player's Phone Number\n");
    fgets(UserInput,7,stdin);
    while(Continue==0){
        Continue = 1;
        if(UserInput[strlen(UserInput)-1] != '\n'){
            int ch = 0;
            while((ch = getchar()) != '\n' && ch != EOF);
        }    
        if (strlen(UserInput)!=5){
            printf("Please Type 4 Characters\n");
            fgets(UserInput,7,stdin);
            Continue = 0;
        }else if(atoi(UserInput)<100){
            printf("Enter a Number\n");
            fgets(UserInput,7,stdin);
            Continue = 0;
        }else{
            Phone = atoi(UserInput);
        }
    }
    return Phone;
}
/*
function: DataCall
purpose: this function displays all the entered data from the previous functions
*/
int DataCall(char f_n[33],char m_n[15],char l_n[33],char s[65],char c[15],int a,int H[1][2],int w,char p[15],int st,double m,char acc[16],int Num[1][3]){
    char UserInput[3];
    char Stars[15] = "Unknown";
    char Weight[15] = "Unknown";
    char lbs[15] = "";
    char Age[15] = "Unknown";
    char qu[15] = "";
    char uu[15] = "";
    char Height1[15] = "Unknown";
    char Height2[15] = "";
    char Money[60] = "Unknown";
    char Num1[20] = "Unknown";
    system("clear");
    f_n[strcspn(f_n,"\n")] = 0;/*these functions remove the new line characters*/
    m_n[strcspn(m_n,"\n")] = 0;
    m_n[strcspn(m_n,"\n")] = 0;
    l_n[strcspn(l_n,"\n")] = 0;
    s[strcspn(s,"\n")] = 0;
    c[strcspn(c,"\n")] = 0;
    p[strcspn(p,"\n")] = 0;
    acc[strcspn(acc,"\n")] = 0;
    if(st<6){
        strcpy(Stars,"");
        if(st==1){
            sprintf(Stars,"*");
        }else if(st==2){
            sprintf(Stars,"**");
        }else if(st==2){
            sprintf(Stars,"***");
        }else if(st==2){
            sprintf(Stars,"****");
        }else if(st==2){
            sprintf(Stars,"*****");
        }
    }
    if(w!=0){
        sprintf(lbs,"lbs");
        sprintf(Weight,"%d",w);
    }
    if(a!=0){
        sprintf(Age,"%d",a);
    }
    if(H[0][0]!=0){
        sprintf(qu,"\"");
        sprintf(uu,"\'");
        sprintf(Height1,"%d",H[0][0]);
        sprintf(Height2,"%d",H[0][1]);
    }
    if(m!=0.001000){
        sprintf(Money,"%f",m);
    }
    if(Num[0][0]!=0){
        sprintf(Num1,"(%d)%d-%d",Num[0][0],Num[0][1],Num[0][2]);
    }
    printf("| Type            | Value           \n");
    printf("|-----------------|-------\n");
    printf("| Name            | %s %s %s        \n",f_n,m_n,l_n);
    printf("| School          | %s              \n",s);
    printf("| Class           | %s              \n",c);
    printf("| Age             | %s              \n",Age);
    printf("| Height          | %s%s%s%s        \n",Height1,uu,Height2,qu);
    printf("| Weight          | %s%s            \n",Weight,lbs);
    printf("| Position        | %s              \n",p);
    printf("| Star Rating     | %s              \n",Stars);
    printf("| NIL Money       | %s              \n",Money);
    printf("| Twitter Account | %s              \n",acc);
    printf("| Phone Number    | %s              \n",Num1);
    printf("|-----------------|-------\n");
    printf("Type Anything to Continue:");
    fgets(UserInput,3,stdin);
    return 0;
}

int main(void){
    char FirstName[33] = "Unknown";
    char MiddleName[15] = "";
    char LastName[33] = "";
    char School[65] = "Unknown";
    char Class[15] = "Unknown";
    int Age = 0;
    int Height[1][2] = {{0,0}};
    int Weight = 0;
    char Position[15] = "Unknown";
    int StarRating = 6;
    double NILMoney = 0.001;
    char TwitterAccount[16] = "Unknown";
    int PhoneNumber[1][3] = {{0,0,0}};
    char UserInput[3];
/*This section simply checks the user input and
calls functions based on what it needs for the option*/
    while(0==0){
        strcpy(UserInput,Display());
    
        if(strcmp(UserInput,"1\n")==0){
            strcpy(FirstName,F_Name());
            strcpy(MiddleName,M_Name());
            strcpy(LastName,L_Name());
        }else if(strcmp(UserInput,"2\n")==0){
            strcpy(School,School_Info());
            strcpy(Class,Class_Info());
        }else if(strcmp(UserInput,"3\n")==0){
            Age = Age_Num();
            Height[0][0] = Height_ft(); 
            Height[0][1] = Height_in(); 
            Weight = Weight_Num();
        }else if(strcmp(UserInput,"4\n")==0){
            strcpy(Position,Position_fn());
            StarRating = Star_Num();
            NILMoney = Money();
        }else if(strcmp(UserInput,"5\n")==0){
            strcpy(TwitterAccount,Twitter());
            PhoneNumber[0][0] = Phone_1();
            PhoneNumber[0][1] = Phone_2();
            PhoneNumber[0][2] = Phone_3();
        }else if(strcmp(UserInput,"6\n")==0){
            DataCall(FirstName,MiddleName,LastName,School,Class,Age,Height,Weight,Position,StarRating,NILMoney,TwitterAccount,PhoneNumber);
        }else if(strcmp(UserInput,"7\n")==0){
            strcpy(FirstName,"Unknown");
            strcpy(MiddleName,"");
            strcpy(LastName,"");
            strcpy(School,"Unknown");
            strcpy(Class,"Unknown");
            Age = 0;
            Height[0][0] = 0;
            Weight = 0;
            strcpy(Position,"Unknown");
            StarRating = 6;
            NILMoney = 0.001;
            strcpy(TwitterAccount,"Unknown");
            PhoneNumber[0][0] = 0;
        }else{
            exit(0);
        }
    }
}