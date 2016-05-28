#ifndef MUSICIAN_H_INCLUDED
#define MUSICIAN_H_INCLUDED

#define FILE_NAME "musician.db"

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

void freeLanser_print(musician_t * fl);
dataBase * createNewDatabase(const char * db_file);
void deleteDatabase(dataBase * self);
musician_t * get_musician(dataBase * self, unsigned int id);
int count_musicians(dataBase * self);

#endif // MUSICIAN_H_INCLUDED
