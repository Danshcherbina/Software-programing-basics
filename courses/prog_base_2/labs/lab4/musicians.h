#ifndef TEACHERS_LIST_H_INCLUDED
#define TEACHERS_LIST_H_INCLUDED

#define BUFFER_LENGTH 100000
#define MSG_LENGTH 10000
#define WORD_LENGTH 100

typedef struct list_s list_t;

typedef struct genre_s{
    char name[10];
    char speciality[20];
    char *instruments[2];
}genre_t;

typedef struct musician_s{
    char name[30];
    char surname[30];
    char date[20];
    int albums;
    double rating;
    genre_t *genre;
} musician_t;

//musicians_list
void musician_update(musician_t *self, char *fname, char *lname, char *date, int albums, double rating, char *cname, char *sname, char *gname1, char *gname2);
musician_t *new_musician(void);
genre_t *new_genre(void);
void free_musician(musician_t *self);
void free_genre(genre_t *self);

list_t *list_new(void);
int list_add(list_t *base, musician_t *self);
int list_find(list_t *base, musician_t *self);
musician_t *list_get(list_t *base, int index);
musician_t *list_remove(list_t *base, int index);
void list_free(list_t *self);
int list_count(list_t *self);
int list_find_id(list_t *self, int id);
int list_id(list_t *self, int index);

//xmlprocess
int musicians_count(char *text);
void xml_extract(char *text, list_t *list);
void xml_out(char *text);
void print_musician(musician_t *self);
char* musician_to_message(musician_t *self, int id);
char* all_musicians_to_message(list_t *list);

#endif // TEACHERS_LIST_H_INCLUDED
