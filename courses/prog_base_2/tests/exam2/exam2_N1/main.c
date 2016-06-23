#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "list.h"

static void getBiggest_listOfStructs_StructWithBiggVal(void **state)
{
    int theValue= 3;
    char * NameVal="KPI";
    int ecName=0;
    int yearVal=1898;
    list_t * l1=list_new();
    list_push_back(l1, university_new("KPI", 1898));
    list_push_back(l1, university_new("NAU", 1930));
    list_push_back(l1, university_new("EIGMU", 2003));
    university_addFac(l1->arr[0], "FPM");
    university_addFac(l1->arr[0], "FIOT");
    university_addFac(l1->arr[0], "FAKS");
    university_addFac(l1->arr[1], "FAAS");
    university_addFac(l1->arr[1], "FAMS");
    university_addFac(l1->arr[2], "FPM");
    university_t * bfu= university_getBiggest(l1);
    assert_int_equal(university_getCnt(bfu), theValue);
    assert_string_equal(university_getName(bfu), NameVal);
    assert_int_equal(university_getFYear(bfu), yearVal);
    list_free(l1);
}

int main()
{
    list_t * l1=list_new();
    list_push_back(l1, university_new("KPI", 1898));
    list_push_back(l1, university_new("NAU", 1930));
    list_push_back(l1, university_new("EIGMU", 2003));
    university_addFac(l1->arr[0], "FPM");
    university_addFac(l1->arr[0], "FIOT");
    university_addFac(l1->arr[0], "FAKS");
    university_addFac(l1->arr[1], "FAAS");
    university_addFac(l1->arr[1], "FAMS");
    university_addFac(l1->arr[2], "FPM");
    university_printAll(l1);
    university_t * bfu= university_getBiggest(l1);
    printf("name of university the biggest university:%s\n", university_getName(bfu));
    printf("year of foundation of the biggest university:%i\n", university_getFYear(bfu));
    list_free(l1);
        const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(getBiggest_listOfStructs_StructWithBiggVal),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
