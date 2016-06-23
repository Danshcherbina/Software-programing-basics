#ifndef UNIVERSITY_H_INCLUDED
#define UNIVERSITY_H_INCLUDED

typedef struct university_s university_t;

typedef struct list_s{
    university_t ** arr;
    int count;
} list_t;

university_t * university_new(char * name, int fYear);
void university_addFac(university_t * self, char * fac);
void university_printAll(list_t * self);
university_t * university_getBiggest(list_t * self);
char * university_getName(university_t * self);
int university_getFYear(university_t * self);
int university_getCnt(university_t * self);

#endif // UNIVERSITY_H_INCLUDED
