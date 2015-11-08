#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const long SLEEP_MILLISECONDS = 40;
    COORD pos;
    pos.X = 59;
    pos.Y = 11;
    int fmt=FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
     SetConsoleTextAttribute(hConsole, fmt);
    for(pos.X=59;pos.X>=10;pos.X--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=10;pos.Y<=14;pos.Y++){
    if(((pos.X>=50&&pos.X<=59)&&(pos.Y>=10&&pos.Y<=14))||((pos.X>=20&&pos.X<=29)&&(pos.Y>=10&&pos.Y<=44))){
    }
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=9;pos.Y>=5;pos.Y--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=10;pos.X<20;pos.X++){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=20;pos.X<70;pos.X++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=5;pos.Y<=9;pos.Y++){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=5;pos.Y<=19;pos.Y++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=60;pos.X<70;pos.X++){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=69;pos.X>=0;pos.X--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=15;pos.Y<=19;pos.Y++){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=19;pos.Y>=0;pos.Y--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=0;pos.X<10;pos.X++){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=0;pos.X<=79;pos.X++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=4;pos.Y>=0;pos.Y--){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.Y=0;pos.Y<=24;pos.Y++){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.X=70;pos.X<=79;pos.X++){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    for(pos.X=79;pos.X>=0;pos.X--){
            Sleep(SLEEP_MILLISECONDS);
    for (pos.Y=20;pos.Y<=24;pos.Y++){
    SetConsoleCursorPosition(hConsole, pos);
    printf("*\n");
    }
    }
    return EXIT_SUCCESS;
}



