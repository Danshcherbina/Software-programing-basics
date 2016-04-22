#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct list_s list_t;

list_t * list_new(void);
void list_free(list_t * self);
int list_getSize(list_t * self);
void list_addBack(list_t * self, char val);
void list_print(list_t * self);
char list_getEl(list_t * self, int index);
void list_setEl(list_t * self, int index, char value);

#endif // LIST_H_INCLUDED
