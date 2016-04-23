#include "main.h"
//#include <stdio.h>

int compare(list_t * self)
{
    int i;
    char el;
    int VowelsCnt=0;
    int ConsonantsCnt=0;
    for(i=0;i<list_getSize(self);i++){
        el=list_getEl(self,i);
        switch(el){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'y':
                VowelsCnt++;
                break;
            case 'b':
            case 'c':
            case 'd':
            case 'f':
            case 'g':
            case 'h':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'v':
            case 'w':
            case 'x':
            case 'z':
                ConsonantsCnt++;
                break;
            default:
                break;
        }
        }
        if (ConsonantsCnt>VowelsCnt){
            return 1;
        }
        else
        {
            return 2;
        }
}
void reaction(list_t * self,int ind)
{
    if (ind==1){
        printf("Consonants win!\n");
    }
    else
        printf("Vowels win!\n");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
