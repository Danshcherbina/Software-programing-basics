#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "musician.h"


list_t *
list_new();

void
list_free(list_t * self);

void
list_push_back(list_t * self, musician_t * ptr);

musician_t *
list_pop_back(list_t * self);

int
list_getCount(list_t * self);

musician_t *
list_getEl(list_t * self, int index);

int list_indById(list_t * self, int id);

#endif // LIST_H_INCLUDED
