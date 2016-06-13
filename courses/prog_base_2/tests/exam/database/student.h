#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#define BUFFER_LENGTH 100000
#define MSG_LENGTH 10000
#define WORD_LENGTH 100

typedef struct student dataBase;
typedef struct student_s
{
    unsigned int markBook;
    char name[100];
    char surname[100];
    char Fname[100];
    char birthday[100];
    char nativeTown[100];

} student_t;
typedef struct list_s{
    student_t ** arr;
    int count;
} list_t;

void student_print(student_t * fl);
dataBase * createNewDatabase(const char * db_file);
void deleteDatabase(dataBase * self);
void get_AllStudent(dataBase * self, list_t * ls);
int count_students(dataBase * self);
int create_student(dataBase *db, student_t *self);

#endif // STUDENT_H_INCLUDED
