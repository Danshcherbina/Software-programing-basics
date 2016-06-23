#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "university.h"

list_t *
list_new();

void
list_free(list_t * self);

void
list_push_back(list_t * self, university_t * ptr);

university_t *
list_pop_back(list_t * self);

int
list_getCount(list_t * self);

university_t *
list_getEl(list_t * self, int index);

#endif // LIST_H_INCLUDED
