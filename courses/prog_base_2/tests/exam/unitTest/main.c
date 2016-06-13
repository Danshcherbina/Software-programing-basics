#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

int sumNumb(const char * myString);

static void sumNumb_mix_OneString_resSumInt(void** state){
    const char * str="H311o my fr13nd -11";
    int sum=313;
    int res=sumNumb(str);
    assert_int_equal(res, sum);
}

static void sumNumb_digitBuyMinus_OneString_resSumInt(void** state){
    const char * str="100-20wqrqw";
    int sum=80;
    int res=sumNumb(str);
    assert_int_equal(res, sum);
}

static void sumNumb_negativeOnly_OneString_resSumInt(void** state){
    const char * str="-100wqrwq -20wqrqw wqrwq-15";
    int sum=-135;
    int res=sumNumb(str);
    assert_int_equal(res, sum);
}

static void sumNumb_neibourMinuses_OneString_resSumInt(void** state){
    const char * str="--100wqrwq --20wqrqw wqrwq-15";
    int sum=-135;
    int res=sumNumb(str);
    assert_int_equal(res, sum);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(sumNumb_mix_OneString_resSumInt),
        cmocka_unit_test(sumNumb_digitBuyMinus_OneString_resSumInt),
        cmocka_unit_test(sumNumb_negativeOnly_OneString_resSumInt),
        cmocka_unit_test(sumNumb_neibourMinuses_OneString_resSumInt),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

int sumNumb(const char * myString){
char buff[100]="";
int cnt=0;
int j;
int total=0;
       for(j = 0; j <strlen(myString); j++){
            if (myString[j]=='-'){
                    if(cnt!=0){
                        total=total+atoi(buff);
                        cnt=0;
                        buff[0]='\0';
                    }
                buff[cnt]=myString[j];
                buff[cnt+1]='\0';
                cnt++;
                continue;
            }else if (isdigit(myString[j])==0){
                    total=total+atoi(buff);
                    cnt=0;
                    buff[0]='\0';
                continue;
            }
            else{
            buff[cnt]=myString[j];
            buff[cnt+1]='\0';
            cnt++;
            if (myString[j+1]=='\0'){
            total=total+atoi(buff);
            }
            }
        }
return total;
}
