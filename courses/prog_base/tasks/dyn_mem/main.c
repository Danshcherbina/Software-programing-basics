#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char * inputStr= NULL;
    int  * count1= NULL;
    int  * count2= NULL;
    int * i=NULL;
inputStr = (char *) malloc(50 * sizeof(char));
count1 = (int  *) malloc( 1 * sizeof(int ));
count2 = (int  *) malloc( 1 * sizeof(int ));
i = (int  *) malloc( 1 * sizeof(int ));
    if (NULL == inputStr || NULL == count1|| NULL == count2|| NULL == i){
        printf("Alloc error");
        return EXIT_FAILURE;
    }
    *count1 = 0;
    *count2 = 0;
    *i = 0;
    printf("Please, input string: ");
    scanf("%s", inputStr);

    for((*i) = 0; (*i) <= 49; (*i)++) {
    if(inputStr[*i] == '('){
        (*count1)++;
    }
    if(inputStr[*i] == ')') {
        (*count2)++;
    }
    if(inputStr[*i] == '\0')
    {
    break;
    }
    }
    printf("Number of vowels1: %i\n", *count1);
    printf("Number of vowels2: %i\n", *count2);
    if ((*count1)==(*count2))
    printf("Result: 1");
    if ((*count2)>(*count1)||(*count2)<(*count1))
    printf("Result: 0");
    free(inputStr);
    free(count1);
    free(count2);
    free(i);
    return EXIT_SUCCESS;
}
