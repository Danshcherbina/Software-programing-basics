#include <stdlib.h>

#include "list.h"
#include "musician.h"

list_t *
list_new() {
    list_t * self = malloc(sizeof(struct list_s));
    self->count = 0;
    self->arr = malloc(0);
    return self;
}

void
list_free(list_t * self) {
    free(self->arr);
    free(self);
}

void
list_push_back(list_t * self, musician_t * ptr) {
    int i;
    for(i=0;i<self->count;i++){
        if(self->arr[i]==NULL){
            self->arr[i]=ptr;
            return;
        }
    }
    self->count++;
    self->arr = realloc(self->arr, sizeof(void *) * self->count);
    self->arr[self->count - 1] = ptr;
}

musician_t *
list_pop_back(list_t * self) {
    self->count--;
    musician_t * ret = self->arr[self->count];
    self->arr = realloc(self->arr, sizeof(void *) * self->count);
    return ret;
}

int
list_getCount(list_t * self) {
    return self->count;
}

musician_t *
list_getEl(list_t * self, int index) {
    return self->arr[index];
}

int list_indById(list_t * self, int id){
    int i;
    for(i=0;i<self->count;i++){
        if(self->arr[i]->id==id){
           return i;
        }
    }
    return -1;
}

void list_delById(list_t * self, int id){
    int i;
    for(i=0;i<self->count;i++){
        if(self->arr[i]->id==id){
           self->arr[i]=NULL;
        }
    }
    return;
}
