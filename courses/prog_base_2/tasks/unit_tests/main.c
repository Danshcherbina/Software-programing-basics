#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "array.h"

 static void new_oneValue_sizeOneValue(void **state)
{
    int theValue= 5;
    array_t array = Array_new(theValue);
    assert_int_equal(Array_getSize(array), theValue);
    Array_delete(array);
}

static void newRand_void_sizeInRangeZeroToTen (void **state)
{
    array_t array = Array_newRand();
    assert_in_range (Array_getSize(array),0, 10);
    Array_delete(array);
}

static void setSize_oneValue_sizeOneValue(void **state)
{
    int theValue1= 5;
    array_t array = Array_new(theValue1);
    int theValue2= 6;
    Array_setSize(array,theValue2);
    assert_int_equal(Array_getSize(array), theValue2);
    Array_delete(array);
}

static void addEl_oneValue_FirstDataOneValue(void **state)
{
    array_t array = Array_new(5);
    int theValue= 6;
    Array_addEl(array,theValue);
    assert_int_equal(Array_getEl(array,0), theValue);
    Array_delete(array);
}

static void delEl_oneValue_FirstDataZero(void **state)
{
    array_t array = Array_new(5);
    int theValue= 6;
    Array_addEl(array,theValue);
    Array_delEl(array,theValue);
    assert_int_equal(Array_getEl(array,0), 0);
    Array_delete(array);
}

static void merge_hasTwoPushedValue_returnsMergedValuesAndSizeOfTwo(void **state)
{
    int theValue= 1;
    array_t array1 = Array_new(theValue);
    array_t array2 = Array_new(theValue);
    int addedEl=6;
    Array_addEl(array1,addedEl);
    Array_addEl(array2,addedEl);
    array_t array3=Array_merge(array1, array2);
    assert_int_equal(Array_getSize(array3), theValue*2);
    int i;
    for(i=0;i<theValue*2;i++){
        assert_int_equal(Array_getEl(array3,i), addedEl);
    }
    Array_delete(array1);
    Array_delete(array2);
    Array_delete(array3);
}


int main(){
 const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_oneValue_sizeOneValue),
        cmocka_unit_test(newRand_void_sizeInRangeZeroToTen),
        cmocka_unit_test(setSize_oneValue_sizeOneValue),
        cmocka_unit_test(addEl_oneValue_FirstDataOneValue),
        cmocka_unit_test(delEl_oneValue_FirstDataZero),
        cmocka_unit_test(merge_hasTwoPushedValue_returnsMergedValuesAndSizeOfTwo),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
return 0;
}
