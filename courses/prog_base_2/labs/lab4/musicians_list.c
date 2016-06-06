#include<stdlib.h>
#include<string.h>

#include "musicians.h"


typedef struct node_s node_t;

struct list_s{
    int count;
    node_t *head;
    node_t *tail;
};

struct node_s {
    node_t *next;
    node_t *prev;
    int id;
    musician_t *contents;
};

void musician_update(musician_t *self, char *fname, char *lname, char *date, int albums, double rating, char *cname, char *sname, char *gname1, char *gname2){
    if(!self)
        return;
    strcpy(self->name, fname);
    strcpy(self->surname, lname);
    strcpy(self->date, date);
    self->albums = albums;
    self->rating = rating;
    strcpy(self->genre->name, cname);
    strcpy(self->genre->speciality, sname);
    strcpy(self->genre->instruments[0], gname1);
    strcpy(self->genre->instruments[1], gname2);
}

musician_t *new_musician(void){
    musician_t *newMusician = malloc(sizeof(struct musician_s));
    newMusician->genre = new_genre();
    return newMusician;
}

genre_t *new_genre(void){
    genre_t *newGen = malloc(sizeof(struct genre_s));
    newGen->instruments[0] = malloc(sizeof(char)*10);
    newGen->instruments[1] = malloc(sizeof(char)*10);
    return newGen;
}

void free_musician(musician_t *self){
    free_genre(self->genre);
    free(self);
}

void free_genre(genre_t *self){
    free(self->instruments[0]);
    free(self->instruments[1]);
    free(self);
}

node_t *node_new(musician_t *content, int id){
    node_t *node = malloc(sizeof(struct node_s));
    node->contents = content;
    node->next = NULL;
    node->prev = NULL;
    node->id = id;
    return node;
}


list_t *list_new(void){
    list_t *list = malloc(sizeof(struct list_s));
    list->count = 0;
    list->head = node_new(NULL, -1);
    list->tail = node_new(NULL, -1);
    list->head->next = list->tail;
    list->tail->prev = list->head;
    return list;
}

int list_add(list_t *base, musician_t *self){
    if(list_find(base, self) != -1)
        return 0;
    node_t *newNode = node_new(self, ++(base->tail->id) + 1);
    node_t *curr = base->tail->prev;
    base->tail->prev = newNode;
    newNode->prev = curr;
    curr->next = newNode;
    newNode->next = base->tail;
    base->count++;
    return newNode->id;
}

int list_find(list_t *base, musician_t *self){
    if(!base->count)
        return -1;
    node_t *curr = base->head->next;
    int i = 0;
    while(NULL != curr->next){
        if(curr->next->contents == self)
            return i;
        curr = curr->next;
        i++;
    }
    return -1;
}

musician_t *list_get(list_t *base, int index){
    if(!base)
        return NULL;
    if(index < 0)
        index = -index;
    if(index >= base->count)
        return NULL;
    node_t *curr = base->head->next;
    for(int i = 0; i < index; i++){
        curr = curr->next;
    }
    return curr->contents;
}

int list_count(list_t *self){
    return self->count;
}

musician_t *list_remove(list_t *base, int index){
    if(!base)
        return NULL;
    if(index < 0)
        index = -index;
    if(index >= base->count || base->count == 0)
        return NULL;
    node_t *curr = base->head->next;
    if(index == 0){
        base->head->next = curr->next;
        curr->next->prev = curr->prev;
        musician_t *teach = curr->contents;
        base->count--;
        free(curr);
        return teach;
    }
    for(int i = 0; i < index; i++){
        curr = curr->next;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    musician_t *teach = curr->contents;
    base->count--;
    free(curr);
    return teach;
}

int list_find_id(list_t *self, int id){
    if(!self)
        return -1;
    node_t *curr = self->head;
    for(int i = 0; i < self->count; i++){
        curr = curr->next;
        if(curr->id == id)
            return i;
    }
    return -1;
}

int list_id(list_t *self, int index){
    if(!self)
        return -1;
    node_t *curr = self->head;
    for(int i = 0; i <= index; i++){
        curr = curr->next;
    }
    return curr->id;
}

void list_free(list_t *self){
    if(!self)
        return;
    while(self->count){
        free_musician(list_remove(self, 0));
    }
    free(self->head);
    free(self->tail);
    free(self);
}
