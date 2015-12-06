#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>

struct article {
   int length;
   int readRate;
   char name[25];
   };

int count(int size, struct article arr[size]);
void change(struct article * pVar, const char * newValue);
void print(struct article * pVar);



int main(){
    int i, e, j;
    int size;
    int counter;
    printf("enter number of articles:");
    scanf("%i", &size);
struct article arr[size];
fflush(stdin);
e=0;
printf("enter %i article names:\n", size);
for (i=0;i<size;i++){
    e++;
    printf("#%i:", e);
    fgets( arr[i].name, 25, stdin);
    }
srand(time(NULL));
 for (i=0;i<size;i++){
    arr[i].length=0+rand()%3001;
    arr[i].readRate=0+rand()%11;
}
e=0;
for(i = 0; i < size; i++) {
        e++;
        printf("article #%i:\n", e);
        printf("article name:%s4article length: %i\narticle reader rating: %i\n", arr[i].name, arr[i].length, arr[i].readRate);
    }
counter=count(size,arr);
printf("number of articles bigger than 1000 words:%i\n", counter);
printf("enter number of article which name you want to change:");
scanf("%i", &i);
i--;
char * newValue="science\n";
struct article * Value=&arr[i];
change(Value, newValue);
printf("name of article #%i was changed to science\n", i+1);
print(Value);
return 0;
}

int count(int size, struct article arr[size]){
    int i;
    int border=1000;
    int res=0;
for (i=0;i<size;i++){
    if (arr[i].length>border){
        res++;
    }
}
return res;
}

void change(struct article * pVar, const char * newValue){
    strcpy(pVar->name, newValue);
return;
}

void print(struct article * pVar){
printf("article name:%sarticle length: %i\narticle reader rating: %i\n", pVar->name, pVar->length, pVar->readRate);
return;
}
