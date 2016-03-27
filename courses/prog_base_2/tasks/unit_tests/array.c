#include <stdio.h>
#include <stdlib.h>
#include "array.h"

struct array_s {
    int size;
    int * data;
};

array_t Array_new(int size) {
    array_t cn = (array_t)malloc(sizeof(struct array_s));
    cn->size = size;
    cn->data = (int *)calloc(cn->size, sizeof(int));
    return cn;
}

array_t Array_newRand(void){
    int i;
    array_t ct=(array_t)malloc(sizeof(struct array_s));
    ct->size=1+rand()%10;
    ct->data = (int *)calloc(ct->size, sizeof(int));
    for(i=0;i<ct->size;i++){
       ct->data[i]=1+rand()%50;
    }
    return ct;
}

void Array_delete(array_t this) {
    free(this->data);
    free(this);
}


int Array_getSize(array_t this) {
    return this->size;
}

int Array_getEl(array_t this, int pos){
return this->data[pos];
}

void Array_setSize(array_t this, int newSize) {
    if (newSize >= 0) {
        this->size = newSize;
    } else {
        this->size = 0;
    }
    this->data = realloc(this->data, sizeof(int) * this->size);
    return;
}

void Array_addEl(array_t this, size_t el){
    int i;
    for (i=0;i<this->size;i++){
        if(this->data[i]==0){
            this->data[i]=el;
            break;
        }
    }
    return;
}

void Array_delEl(array_t this, size_t el){
    int i;
    for (i=0;i<this->size;i++){
        if(this->data[i]==el){
            this->data[i]=0;
            break;
        }
    }
    return;
}

array_t Array_merge(array_t ar1, array_t ar2){
    int i;
    int els=ar1->size+ar2->size;
    array_t mrg=Array_new(els);
    for(i=0;i<ar1->size;i++){
        Array_addEl(mrg, ar1->data[i]);
    }
    for(i=0;i<ar2->size;i++){
        Array_addEl(mrg, ar2->data[i]);
    }
    return mrg;
}

void Array_print(array_t a1){
    int i;
    for (i=0;i<a1->size;i++){
        if(a1->data[i]!=0){
            printf("%i ", a1->data[i]);
        }
    }
}
