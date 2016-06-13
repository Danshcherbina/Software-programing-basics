#ifndef MUSICIAN_H_INCLUDED
#define MUSICIAN_H_INCLUDED
#define FILE_NAME "musician.db"
#define BUFFER_LENGTH 100000
#define MSG_LENGTH 10000
#define WORD_LENGTH 100
typedef struct musician dataBase;
typedef struct musician_s
{
    unsigned int id;
    char name[100];
    char surname[100];
    double salary;
    int instr;
    char birthDate[100];

} musician_t;
typedef struct list_s{
    musician_t ** arr;
    int count;
} list_t;
void musician_print(musician_t * fl);
dataBase * createNewDatabase(const char * db_file);
void deleteDatabase(dataBase * self);
musician_t * get_musician(dataBase * self, unsigned int id);
int count_musicians(dataBase * self);
void get_AllMusician(dataBase * self , list_t * ls);
int delete_musician(dataBase *db, int id);
int create_musician(dataBase *db, musician_t *self);
void select_musicians(dataBase *db, list_t * list, int filter1, double filter2, int state);

char * musicianToString(musician_t * self);
char * musiciansToString(list_t * self);
#endif // MUSICIAN_H_INCLUDED
