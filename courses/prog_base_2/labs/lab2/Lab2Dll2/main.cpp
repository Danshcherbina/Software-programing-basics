#include "main.h"

int compare(list_t * self)
{
    int i;
    char el;
    int Cnt=0;
    for(i=0;i<list_getSize(self);i++){
        el=list_getEl(self,i);
        if(el==' '){
            Cnt++;
        }
    }
        if (Cnt>5){
            return 1;
        }
        else
        {
            return 2;
        }
}

void reaction(list_t * self,int ind)
{
    int i;
    char el;
    if (ind==1){
        for(i=0;i<list_getSize(self);i++){
            el=list_getEl(self,i);
            if(' '==el){
                list_setEl(self,i,'_');
            }
        }
    }
    else
        return;
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
