#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <windows.h>
#include "thread.h"
#include "mutex.h"
typedef struct added_s {
    char sChar[10];
    mutex_t * mu;
} added_t;

void * printerFunc(void * args) {
    int i,j;
    j=1;
    added_t * printed = (added_t *)args;
    while(j<=2){
    mutex_lock(printed->mu);
                for(i=1;i<=10;i++){
                        //mutex_lock(shared->mu);
            printf("%s", printed->sChar);
            //mutex_unlock(shared->mu);
            Sleep(500);
                }
        mutex_unlock(printed->mu);
        Sleep(500);
        j++;
    }
    return NULL;
}

int main(void) {
    added_t printedData1={{'T','o','m','\0'}, mutex_new()};
    added_t printedData2={{'G','o','\0'}, printedData1.mu};
    added_t printedData3={{'T','o','\0'},printedData1.mu};
    thread_t * printer1 = thread_create_args(printerFunc, &printedData1);
    thread_t * printer2 = thread_create_args(printerFunc, &printedData2);
    thread_t * printer3 = thread_create_args(printerFunc, &printedData3);
    thread_join(printer1);
    thread_join(printer2);
    thread_join(printer3);
    thread_free(printer1);
    thread_free(printer2);
    thread_free(printer3);
    mutex_free(printedData1.mu);
    mutex_free(printedData2.mu);
    mutex_free(printedData3.mu);
    return 0;
}

