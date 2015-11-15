#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main(void) {
    const long SLEEP_MILLISECONDS= 40;
    int fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 59;
    pos.Y = 11;
    fmt=BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN ;
     SetConsoleTextAttribute(hConsole, fmt);
    for(pos.X=59;pos.X>=10;pos.X--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=10;pos.Y<=14;pos.Y++){
    if (pos.Y>=10&&pos.Y<=14){
        switch (pos.X/10){
    case 5:
    case 2:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 4:
    case 3:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 1:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=9;pos.Y>=5;pos.Y--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=10;pos.X<20;pos.X++){
    if (pos.X>=10&&pos.X<20){
        switch (pos.Y/5){
    case 1:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=20;pos.X<70;pos.X++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=5;pos.Y<=9;pos.Y++){
    if (pos.Y>=5&&pos.Y<=9){
        switch (pos.X/10){
    case 1:
    case 4:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 2:
    case 3:
    case 6:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 5:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=5;pos.Y<=19;pos.Y++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=60;pos.X<70;pos.X++){
    if (pos.X>=60&&pos.X<70){
        switch (pos.Y/5){
    case 2:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
    case 3:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=69;pos.X>=0;pos.X--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=15;pos.Y<=19;pos.Y++){
    if (pos.Y>=15&&pos.Y<=19){
        switch (pos.X/10){
    case 0:
    case 3:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 1:
    case 4:
    case 5:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 2:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=19;pos.Y>=0;pos.Y--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=0;pos.X<10;pos.X++){
        if (pos.X>=0&&pos.X<10){
        switch (pos.Y/5){
    case 1:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
    case 0:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN;
        break;
    case 2:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=0;pos.X<=79;pos.X++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=4;pos.Y>=0;pos.Y--){
    if (pos.Y>=0&&pos.Y<=4){
        switch (pos.X/10){
    case 6:
    case 3:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 1:
    case 2:
    case 5:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 4:
    case 7:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=0;pos.Y<=24;pos.Y++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=70;pos.X<=79;pos.X++){
        if (pos.X>=70&&pos.X<=79){
        switch (pos.Y/5){
    case 3:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
    case 1:
    case 4:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN;
        break;
    case 2:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=79;pos.X>=0;pos.X--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=20;pos.Y<=24;pos.Y++){
    if (pos.Y>=20&&pos.Y<=24){
        switch (pos.X/10){
    case 1:
    case 4:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 2:
    case 5:
    case 6:
        fmt=BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN ;
        break;
    case 0:
    case 3:
        fmt=BACKGROUND_INTENSITY| BACKGROUND_GREEN;
        break;
        }
    SetConsoleTextAttribute(hConsole, fmt);
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    pos.X = 0;
    pos.Y = 27;
    SetConsoleCursorPosition(hConsole, pos);
    return EXIT_SUCCESS;
}



