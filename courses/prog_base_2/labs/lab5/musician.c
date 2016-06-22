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
    if(fl==NULL){
        printf("Error, NULL pointer");
        return;
    }
    printf("\nId:%i\nName: %s\nSurname: %s\nSalary: %0.2f\nInstruments: %i\nBirth date: %s\n\n",
         fl->id,fl->name, fl->surname, fl->salary, fl->instr,fl->birthDate);
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
    free(self->db);
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
    int rc = sqlite3_prepare_v2(self->db, sql, strlen(sql) , &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    if(SQLITE_OK != rc){
        return NULL;
    }
    while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            return NULL;
        }
        else {
            if(SQLITE_DONE == rc){
                printf("\nRead request processed");
                break;
            }
            fl = malloc(sizeof(musician_t));
            fill_musician(stmt, fl);
    }
    }
    sqlite3_finalize(stmt);
    return fl;
}

void get_AllMusician(dataBase * self, list_t * ls)
{
    sqlite3_stmt * stmt;
    char * sql = "SELECT  * FROM musician ";
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
            musician_t * fl = NULL;
            fl = malloc(sizeof(musician_t));
            fill_musician(stmt, fl);
            list_push_back(ls, fl);
        }
    }
    sqlite3_finalize(stmt);
    return;
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

int delete_musician(dataBase *db, int id){
    sqlite3_stmt *stmt = NULL;
    const char *sql = "DELETE FROM musician WHERE id = ?;";
    int rc = sqlite3_prepare_v2(db->db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    if(SQLITE_OK != rc){
        return 0;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        return 0;
    }
    printf("\nDelete request processed\n");
    sqlite3_finalize(stmt);
    return 1;
}

int create_musician(dataBase *db, musician_t *self){
    sqlite3_stmt *stmt = NULL;
    const char *sql;
    sql = "INSERT INTO musician VALUES (?,?,?,?,?,?);";
    int rc = sqlite3_prepare_v2(db->db, sql, strlen(sql)+1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, self->id);
    sqlite3_bind_text(stmt, 2, self->name, strlen(self->name), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, self->surname, strlen(self->surname), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, self->salary);
    sqlite3_bind_int(stmt, 5, self->instr);
    sqlite3_bind_text(stmt, 6, self->birthDate, strlen(self->birthDate), SQLITE_TRANSIENT);
    if(SQLITE_OK != rc){
        return 0;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        return 0;
    }
    printf("\nCreate request processed.");
    sqlite3_finalize(stmt);
    return 1;
}

void select_musicians(dataBase *db, list_t * list, int filter1, double filter2, int state){
    sqlite3_stmt *stmt = NULL;
    const char *sql = malloc(1000);
    switch(state){
case 7:
    sprintf(sql, "SELECT * FROM musician WHERE IncomePerMonth > ?1 AND MusInstr > ?2;");
    break;
case 6:
    sprintf(sql, "SELECT * FROM musician WHERE IncomePerMonth < ?1 AND MusInstr > ?2;");
    break;
case 3:
    sprintf(sql, "SELECT * FROM musician WHERE IncomePerMonth > ?1 AND MusInstr < ?2;");
    break;
case 2:
    sprintf(sql, "SELECT * FROM musician WHERE IncomePerMonth < ?1 AND MusInstr < ?2;");
    break;
    default:
    break;
    }
    int rc = sqlite3_prepare_v2(db->db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 2, filter1);
    sqlite3_bind_double(stmt, 1, filter2);
    if(SQLITE_OK != rc){
        return;
    }
     while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            return;
        }
        else {
            if(SQLITE_DONE == rc){
                printf("\nSelect request processed.");
                break;
            }
            musician_t *self = malloc(sizeof(musician_t));
            fill_musician(stmt, self);
            list_push_back(list, self);
        }
    }
    free(sql);
    sqlite3_finalize(stmt);
}

