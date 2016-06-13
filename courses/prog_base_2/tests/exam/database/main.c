#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sqlite3.h>
#include "list.h"
#include "student.h"

#define MAXBUFLEN 20480
#define NO_FLAGS_SET 0

int main(int argc, char *argv[])
{
    int i;
    list_t * l1=list_new();
    dataBase * db = createNewDatabase(argv[1]);
    student_t *t1 = malloc(sizeof(struct student_s));
        strcpy(t1->name, "Donkey");
        strcpy(t1->surname, "Kong");
        strcpy(t1->Fname, "Kong");
        strcpy(t1->birthday, "12.12.14");
        strcpy(t1->nativeTown, "gagaga");
        t1->markBook = 2;
    create_student(db, t1);
    get_AllStudent(db, l1);
    for(i=0;i<l1->count;i++){
        student_print(l1->arr[i]);
    }
    free(t1);
    deleteDatabase(db);
    return 0;
}
