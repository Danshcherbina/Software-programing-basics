#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "stack.h"
#include "list.h"

typedef struct client_s {
    char fraze[100];
} client_t;

void client_endCycle(void * receiver){
    client_t * client=(client_t *)receiver;
    printf("%s\n", client->fraze);
}

static void new_void_CountZero(void **state)
{
    int theValue= 0;
    stack_t * s1=stack_new();
    assert_int_equal(stack_getCount(s1), theValue);
    stack_free(s1);
}

static void push_OneValue_CountOne(void **state)
{
    int cVal=1;
    int theValue= 4;
    stack_t * s1=stack_new();
    stack_push(s1, theValue);
    assert_int_equal(stack_getCount(s1), cVal);
    stack_free(s1);
}

static void pop_void_CountZeroReturnVal(void **state)
{
    int cVal=0;
    int theValue= 4;
    int iVal;
    stack_t * s1=stack_new();
    stack_push(s1, theValue);
    iVal=stack_pop(s1);
    assert_int_equal(stack_getCount(s1), cVal);
    assert_int_equal(iVal, theValue);
    stack_free(s1);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_CountZero),
        cmocka_unit_test(push_OneValue_CountOne),
        cmocka_unit_test(pop_void_CountZeroReturnVal),

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
    srand(time(NULL));
    int i;
    stack_t * s1=stack_new();
    stack_t * s2=stack_new();
    for(i=0;i<6;i++){
        stack_push(s1, 5);
        stack_push(s2, 6);
    }
    client_t clients[4]={{"OMG!!"},{"Finally!!"},{"At last!"},{"Is it over?"}};
    for(i=0;i<4;i++){
        stack_subscribeEmpNFull(s1,&clients[i], client_endCycle);
        stack_subscribeEmpNFull(s2,&clients[i], client_endCycle);
    }
    stack_subscribeEmp(s1,s2,stack_getEmpFn(s1));
    stack_subscribeEmp(s2,s1,stack_getEmpFn(s2));
    stack_subscribeFull(s1,s2,stack_getFullFn(s1));
    stack_subscribeFull(s2,s1,stack_getFullFn(s2));
        stack_print(s1);
        printf("\n");
        stack_print(s2);
        Sleep(2000);
        system("cls");
    while(1){
        int chs=0;
        int val=0;
        chs=1+ rand()%2;
        val=-10+rand()%21;
        switch(chs){
        case 1:
            {
                if(val>=0){
                    stack_push(s1,val);
                }
                if(val<0){
                    stack_pop(s1);
                }
                break;
            }
        case 2:
            {
                if(val>=0){
                    stack_push(s2,val);
                }
                if(val<0){
                    stack_pop(s2);
                }
                 break;
            }
        }
        stack_print(s1);
        printf("\n");
        stack_print(s2);
        Sleep(2000);
        system("cls");
    }
    stack_free(s1);
    stack_free(s2);
    return 0;
}
