#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

typedef struct array_s * array_t;
array_t Array_new(int size);
array_t Array_newRand(void);
void Array_delete(array_t this);
int Array_getSize(array_t this);
void Array_setSize(array_t this, int newSize);
void Array_addEl(array_t this, size_t el);
void Array_delEl(array_t this, size_t el);
array_t Array_merge(array_t ar1, array_t ar2);
void Array_print(array_t this);
int Array_getEl(array_t this, int pos);

#endif // ARRAY_H_INCLUDED
