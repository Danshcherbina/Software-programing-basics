#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

void prinArray(int size, char myString[][100]);
void slength(int size, int res[],const char myString[][100]);
void maxlength(int size, char myString[][100]);
void minlength(int size, char myString[][100]);
void fillRand(int size, int l, char myString[][100]);
void swapmm(int size, char myString[][100]);
void lessp(int size, int f, char myString[][100] );
void bigp(int size, int b, char myString[][100] );
void wordcount(int size,char myString[][100]);
void checknumb(int size, char myString[][100]);
void help();
void reprinArray(int size, char myString[][100]);
int main()
{
    const long SLEEP_MILLISECONDS= 2000;
    int opr;
    int k=0;
    int i, size;
    int fmt;
    const char cmd[20];
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     for (pos.X=2;pos.X<78;pos.X++){
            for (pos.Y=2;pos.Y<12;pos.Y++){
            fmt= BACKGROUND_GREEN;
            SetConsoleTextAttribute(hConsole, fmt);
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
            }
            }
     for (pos.X=1;pos.X<79;pos.X++){
        pos.Y=1;
        SetConsoleCursorPosition(hConsole, pos);
        printf("*");
        pos.Y=12;
        SetConsoleCursorPosition(hConsole, pos);
        printf("*");
     }
     for (pos.Y=1;pos.Y<12;pos.Y++){
        pos.X=1;
        SetConsoleCursorPosition(hConsole, pos);
        printf("*");
        pos.X=78;
        SetConsoleCursorPosition(hConsole, pos);
        printf("*");
     }
     while(1){
    pos.X = 18;
    pos.Y = 2;
    SetConsoleCursorPosition(hConsole, pos);
    printf("enter string array size[1..8], please enter only numbers:");
    scanf("%d", &size);
    if (size>9||size<=0){
        pos.X = 30;
        pos.Y = 3;
        SetConsoleCursorPosition(hConsole, pos);
        printf("invalid input, please try again");
        for(pos.X = 60;pos.X<78;pos.X++){
        pos.Y = 2;
        SetConsoleCursorPosition(hConsole, pos);
        printf(" ");
        }
        continue;
    }
    break;
     }
    fflush(stdin);
    char myString [size][100];
    int res[size];
    prinArray(size,myString);
    while (1){
            int a=0;
            opr=0;
        fmt=FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
        SetConsoleTextAttribute(hConsole,fmt );
        for (pos.X=20;pos.X<79;pos.X++){
            pos.Y=13;
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
        }
        for (pos.X=2;pos.X<79;pos.X++){
            pos.Y=14;
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
        }
        pos.X=0;
        pos.Y=13;
        SetConsoleCursorPosition(hConsole, pos);
        printf("enter your command(help to see available commands):\n");
        printf(">>");
        scanf("%s",&cmd);
        if(strcmp(cmd,"help")==0){
           help();
            a++;
        }
        if(strcmp(cmd,"exit")==0){
            system("cls");
           return EXIT_SUCCESS;
        }
        if (strcmp(cmd,"length")==0){
        slength(size,res,myString);
        a++;
        }
        if (strcmp(cmd,"max")==0){
        maxlength(size, myString);
        a++;
        }
        if (strcmp(cmd,"min")==0){
        minlength(size, myString);
        a++;
        }
        if (strcmp(cmd,"swap")==0){
        swapmm(size, myString);
        a++;
        }
        if (strcmp(cmd,"fill")==0){
        fillRand( size,  opr, myString);
        a++;
        }
        if (strcmp(cmd,"shows")==0){
        lessp( size, opr, myString);
        a++;
        }
        if (strcmp(cmd,"showl")==0){
        bigp( size, opr, myString);
        a++;
        }
        if (strcmp(cmd,"wordc")==0){
        wordcount(size,myString);
        a++;
        }
        if (strcmp(cmd,"checkn")==0){
        checknumb(size,myString);
        a++;
        }
        if (0==a){
            pos.X=0;
            pos.Y=15;
            SetConsoleCursorPosition(hConsole, pos);
            printf("unknown comand, try again");
            Sleep(SLEEP_MILLISECONDS);
        }
        for (pos.X=0;pos.X<78;pos.X++){
            for (pos.Y=15;pos.Y<27;pos.Y++){
            fmt= FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN;
            SetConsoleTextAttribute(hConsole, fmt);
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
            }
            }
    }
}

void prinArray(int size, char myString[][100]){
    int k=0;
    int e=0;
    int i, j;
    int fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     for (pos.X=2;pos.X<78;pos.X++){
            for (pos.Y=2;pos.Y<12;pos.Y++){
            fmt= BACKGROUND_GREEN;
            SetConsoleTextAttribute(hConsole, fmt);
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
            }
            }
    pos.X=30;
    pos.Y=2;
    SetConsoleCursorPosition(hConsole, pos);
    printf("enter %i lines<46:\n", size);
for (i=0;i<size;i++){
        e++;
        pos.X=30;
        pos.Y=2+e;
        SetConsoleCursorPosition(hConsole, pos);
    printf("#%i:", e);
    fgets( myString[i], 45, stdin);
    printf("\n");
    }
for (i=0;i<size;i++){
    j = strlen(myString[i])-1;
  if(myString[i][j]=='\n')
    myString[i][j] = '\0';
}
    pos.X=30;
    pos.Y=2;
    SetConsoleCursorPosition(hConsole, pos);
    printf("here are your string array:\n");
    for (i=0;i<size;i++){
    k++;
    pos.X=30;
    pos.Y=2+k;
    SetConsoleCursorPosition(hConsole, pos);
    printf( "%i: %s\n",k, myString[i] );
    }
return;
}

void slength(int size, int res[],const char myString[][100]){
    int n;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
    for (n=0;n<size;n++){
    res[n]= strlen(myString[n]);
    }
    pos.Y=16;
    for (n=0;n<size;n++){
    pos.X=3;
    SetConsoleCursorPosition(hConsole, pos);
    printf("%i string length: %i\n",n+1,res[n]);
    pos.Y++;
    }
    fflush(stdin);
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}

void maxlength(int size, char myString[][100]){
    int n;
    char* maxln;
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
    maxln=myString[0];
    for (n=0;n<size;n++){
    if (strlen(myString[n])>strlen(maxln))
    maxln= myString[n];
    }
    pos.X=3;
    pos.Y=15;
    SetConsoleCursorPosition(hConsole, pos);
    printf("max String:%s", maxln);
    fflush(stdin);
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}

void minlength(int size, char myString[][100]){
    int n;
    char* minln;
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
    minln=myString[0];
    for (n=0;n<size;n++){
    if (strlen(myString[n])<=strlen(minln))
    minln= myString[n];
    }
    pos.X=3;
    pos.Y=15;
    SetConsoleCursorPosition(hConsole, pos);
    printf("min String:%s", minln);
    fflush(stdin);
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}

void swapmm(int size, char myString[][100]){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
int n;
    char* maxln;
    char* minln;
    int max=0;
    int min=0;
    int k=0;
    maxln=myString[0];
    minln=myString[0];
    for (n=0;n<size;n++){
    if (strlen(myString[n])>strlen(maxln)){
    maxln= myString[n];
    max=n;
    }
    if (strlen(myString[n])<=strlen(minln)){
    minln= myString[n];
    min=n;
    }
    }
    pos.X=24;
    pos.Y=13;
    SetConsoleCursorPosition(hConsole, pos);
    printf("array with swapped lines:");
    pos.X=24;
    pos.Y++;
     for (n=0;n<size;n++){
            pos.X=24;
            SetConsoleCursorPosition(hConsole, pos);
    k++;
    if (n==min){
        printf( "#%i: %s\n",k, maxln);
        pos.Y++;
        continue;
    }
    if (n==max){
        printf( "#%i: %s\n",k, minln);
        pos.Y++;
        continue;
    }
    printf( "#%i: %s\n",k, myString[n] );
    pos.Y++;
    }
     fflush(stdin);
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}

void fillRand(int size, int l, char myString[][100]){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     fflush(stdin);
        pos.X=0;
        pos.Y=15;
        SetConsoleCursorPosition(hConsole, pos);
        printf("enter lines length[1..45]:\n");
        pos.X=0;
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        scanf("%i",&l);
     int fmt;
    int i,j,g;
    for (i=0;i<size;i++){
    g=strlen(myString[i]);
        for (j=0;j<g;j++){
    myString[i][j]=0;
    }
    }
    int k=0;
    for (i=0;i<size;i++){
        for (j=0;j<l;j++){
    myString[i][j]=97+rand()%26;
    }
    }
    k=0;
    for (pos.X=2;pos.X<78;pos.X++){
            for (pos.Y=2;pos.Y<12;pos.Y++){
            fmt= BACKGROUND_GREEN;
            SetConsoleTextAttribute(hConsole, fmt);
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
            }
            }
    pos.X=30;
    pos.Y=2;
    SetConsoleCursorPosition(hConsole, pos);
    printf("here are your string array:\n");
    for (i=0;i<size;i++){
    k++;
    pos.X=30;
    pos.Y=2+k;
    SetConsoleCursorPosition(hConsole, pos);
    printf( "%i: %s\n",k, myString[i] );
    }
    return;
    }

void lessp(int size, int f, char myString[][100] ){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     fflush(stdin);
        pos.X=0;
        pos.Y=15;
        SetConsoleCursorPosition(hConsole, pos);
        printf("enter integer length[1..45]:\n");
        pos.X=0;
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        scanf("%i",&f);
int i,j,g;
int k=1;
pos.X=30;
    pos.Y=13;
    SetConsoleCursorPosition(hConsole, pos);
printf("lines shorter than %i:\n", f);
    for (i=0;i<size;i++){
    g=strlen(myString[i]);
    if (g<f){
    pos.X=30;
    pos.Y=13+k;
    SetConsoleCursorPosition(hConsole, pos);
    printf( "%s\n",myString[i]);
    k++;
    }
    }
     fflush(stdin);
    pos.X=3;
    pos.Y=18;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}
void bigp(int size, int b, char myString[][100] ){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     fflush(stdin);
        pos.X=0;
        pos.Y=15;
        SetConsoleCursorPosition(hConsole, pos);
        printf("enter integer length[1..45]:\n");
        pos.X=0;
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        scanf("%i",&b);
int i,j,g;
int k=1;
pos.X=30;
    pos.Y=13;
    SetConsoleCursorPosition(hConsole, pos);
printf("lines longer than %i:\n", b);
    for (i=0;i<size;i++){
    g=strlen(myString[i]);
    if (g>b){
    pos.X=30;
    pos.Y=13+k;
    SetConsoleCursorPosition(hConsole, pos);
    printf( "%s\n",myString[i]);
    k++;
    }
    }
     fflush(stdin);
    pos.X=3;
    pos.Y=18;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}

void wordcount(int size,char myString[][100]){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
int count;
int i;
int k=0;
char *pstr;
    for (i=0;i<size;i++){
            count=0;
            k++;
    pstr=strtok(myString[i],"  1234567890-=+_$#@;:.,?*");
    while (pstr!=NULL)
        {
        pstr=strtok(NULL,"  1234567890-=+_$#@;:.,?*");
        count++;
        }
         pos.X=3;
        pos.Y=14+k;
        SetConsoleCursorPosition(hConsole, pos);
        printf("Words in %i line - %d\n",k, count);
        }
    fflush(stdin);
    pos.X=3;
    pos.Y=23;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}

void checknumb(int size, char myString[][100]){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
int i,j, flag,v,k;
    k=0;
    for (i=0;i<size;i++){
            k++;
            flag=1;
            v=strlen(myString[i]);
    if (myString[i][0] != '-' && !isdigit(myString[i][0])){
        flag = 0;
        }
    else{
        for(j = 1; j < v; j++){
            if (!isdigit(myString[i][j]))
            {
                flag = 0;
                break;
           }
        }
    }
        pos.X=3;
        pos.Y=14+k;
        SetConsoleCursorPosition(hConsole, pos);
    printf("line %i:", k);
    if (flag == 0){
        printf("number not found");
    }
    if (flag!=0){
    for(j = 0; j <v; j++){
             printf("%c",myString[i][j] );
    }
    }
    printf("\n");
    }
    fflush(stdin);
    pos.X=3;
    pos.Y=23;
    SetConsoleCursorPosition(hConsole, pos);
    printf("press enter to continue");
    pos.X=3;
    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    getchar();
    return;
}
void help(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    fflush(stdin);
    int fmt=FOREGROUND_RED|FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole,fmt);
printf("help \n");
printf("length 0\n");
printf("max \n");
printf("min \n");
printf("fill $i\n");
printf("swap \n");
printf("shows $i\n");
printf("showl $i\n");
printf("wordc \n");
printf("checkn \n");
printf("exit \n");
fmt=FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN;
SetConsoleTextAttribute(hConsole,fmt);
printf("press enter to continue");
pos.Y=15;
pos.X=10;
SetConsoleCursorPosition(hConsole, pos);
printf(" show available commands\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" print length of all lines\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" show the longest line\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" show the shortest line\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" fill array with random lines length=$i\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" swap the longest and the shortest lines\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" show lines which are shorter than $i\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" show lines which are longer than $i\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" show number of words in all lines one buy one\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" check out all terms of whether they contain only integer\n");
pos.Y++;
SetConsoleCursorPosition(hConsole, pos);
printf(" end program\n");
pos.X=0;
pos.Y=27;
SetConsoleCursorPosition(hConsole, pos);
getchar();
return;
}
