#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "list.h"

struct student {
    sqlite3 * db;
};

void student_print(student_t * fl) {
    if(fl==NULL){
        printf("Error, NULL pointer");
        return;
    }
    printf("\nmarkBook:%i\nName: %s\nSurname: %s\nFather name: %s\nBirthday: %s\nNative town:%s\n\n",
         fl->markBook,fl->name, fl->surname, fl->Fname, fl->birthday,fl->nativeTown);
}

dataBase * createNewDatabase(const char * db_file)
{
    dataBase * self = malloc(sizeof(struct student));
    int rc = 0;
    rc = sqlite3_open(db_file, &(self->db));
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void deleteDatabase(dataBase * self)
{
    sqlite3_close(self->db);
    free(self->db);
    free(self);
}

static void fill_student(sqlite3_stmt * stmt, student_t * fl)
{
    const unsigned char * name = sqlite3_column_text(stmt, 0);
    const unsigned char * surname = sqlite3_column_text(stmt, 1);
    const unsigned char * Fname = sqlite3_column_text(stmt, 2);
    const unsigned char * birthay =  sqlite3_column_text(stmt, 3);
    const unsigned char * nativeTown =  sqlite3_column_text(stmt, 4);
    int markBook = sqlite3_column_int(stmt, 5);
    strcpy(fl->name, (char *)name);
    strcpy(fl->surname, (char *)surname);
    strcpy(fl->Fname, (char *)Fname);
    strcpy(fl->birthday, (char *)birthay);
    strcpy(fl->nativeTown, (char *)nativeTown);
    fl->markBook = markBook;
}

void get_AllStudent(dataBase * self, list_t * ls)
{
    sqlite3_stmt * stmt;
    char * sql = "SELECT  * FROM Student ";
    int rc = sqlite3_prepare_v2(self->db, sql, strlen(sql), &stmt, NULL);
        while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            return;
        }
        else {
            if(SQLITE_DONE == rc){
                printf("\nRead request processed\n");
                break;
            }
            student_t * fl = NULL;
            fl = malloc(sizeof(student_t));
            fill_student(stmt, fl);
            list_push_back(ls, fl);
        }
    }
    sqlite3_finalize(stmt);
    return;
}

int count_students(dataBase * self)
{
    sqlite3_stmt * stmt = NULL;
    const char * sql = "SELECT COUNT(*) FROM Student;";
    sqlite3_prepare_v2(self->db, sql, -1, &stmt, NULL);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

int create_student(dataBase *db, student_t *self){
    sqlite3_stmt *stmt = NULL;
    const char *sql;
    sql = "INSERT INTO Student VALUES (?,?,?,?,?,?);";
    int rc = sqlite3_prepare_v2(db->db, sql, strlen(sql)+1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, self->name, strlen(self->name), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, self->surname, strlen(self->surname), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, self->Fname, strlen(self->Fname), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, self->birthday, strlen(self->birthday), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, self->nativeTown, strlen(self->nativeTown), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, self->markBook);
    if(SQLITE_OK != rc){
        return 0;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        return 0;
    }
    printf("\nCreate request processed.");
    sqlite3_finalize(stmt);
    return 1;
}

