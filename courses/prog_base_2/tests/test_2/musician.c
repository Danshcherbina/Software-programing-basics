#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_NAME "musician"

#include "musician.h"

struct musician {
    sqlite3 * db;
};

void musician_print(musician_t * fl) {
    printf("\nName: %s\nSurname: %s\nSalary: %0.2f\nInstruments: %i\nBirth date: %s\n\n",
        fl->name, fl->surname, fl->salary, fl->instr,fl->birthDate);
}

dataBase * createNewDatabase(const char * db_file)
{
    dataBase * self = malloc(sizeof(struct musician));
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
    free(self);
}

static void fill_musician(sqlite3_stmt * stmt, musician_t * fl)
{
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    double salary = sqlite3_column_double(stmt, 3);
    int instr = sqlite3_column_int(stmt, 4);
    const unsigned char * birthDate =  sqlite3_column_text(stmt, 5);
    strcpy(fl->name, (char *)name);
    strcpy(fl->surname, (char *)surname);
    fl->id = id;
    fl->instr = instr;
    fl->salary = salary;
    strcpy(fl->birthDate, (char *)birthDate);
}

musician_t * get_musician(dataBase * self, unsigned int id)
{
    musician_t * fl = NULL;
    sqlite3_stmt * stmt;
    char * sql = "SELECT  * FROM musician "
                 "WHERE Id = ?";
    sqlite3_prepare_v2(self->db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    fl = malloc(sizeof(musician_t));
    fl->id = id;
    fill_musician(stmt, fl);
    sqlite3_finalize(stmt);
    return fl;
}

int count_musicians(dataBase * self)
{
    sqlite3_stmt * stmt = NULL;
    const char * sql = "SELECT COUNT(*) FROM " TABLE_NAME ";";
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
