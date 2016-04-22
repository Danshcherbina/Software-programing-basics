#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "list.h"

typedef int (*cmp_f)(list_t * self);
typedef void (*react_f)(list_t * self,int ind);

typedef struct dynamic_s {
    HANDLE hLib;
    cmp_f cmp;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();

int main(void) {
    const int MAX_LIST_SIZE = 10;
    list_t * list = list_new();
    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->cmp) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");
    char el;
    while (list_getSize(list) < MAX_LIST_SIZE) {
        el=0;
        printf("Add symbol(there is no need to press ENTER):");
        el=getche();
        printf("\n");
        list_addBack(list, el);
        list_print(list);
        Sleep(500);
    }
    int res;
    res=dll->cmp(list);
    dll->react(list, res);
    list_print(list);
    list_free(list);
    return 0;
}

const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. Lab2Dll1\n2. Lab2Dll2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "Lab2Dll1.dll";
        } else if (dllNum == 2) {
            return "Lab2Dll2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->cmp = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->cmp = (cmp_f)GetProcAddress(dyn->hLib, "compare");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
