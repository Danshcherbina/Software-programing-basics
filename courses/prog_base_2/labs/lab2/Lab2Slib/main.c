#include "list.h"

struct list_s{
    char array[100];
    int size;
};

list_t * list_new(void)
{
    list_t * l=malloc(sizeof(struct list_s));
    l->size=0;
    return l;
}

void list_free(list_t * self)
{
    free(self);
}

int list_getSize(list_t * self) {
    return self->size;
}

void list_addBack(list_t * self, char val) {
    self->array[self->size] = val;
    self->size += 1;
}

void list_print(list_t * self) {
    int i;
    printf("List:");
    for(i = 0; i < self->size; i++) {
        printf("%3c ", self->array[i]);
    }
    printf("\n");
}

char list_getEl(list_t * self, int index)
{
    return self->array[index];
}

void list_setEl(list_t * self, int index, char value){
    self->array[index]=value;
}
