#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sqlite3.h>
#include <winsock2.h>
#include <winsock.h>
#include <time.h>
#include "cJSON.h"
#include "musician.h"

#define MAXBUFLEN 20480
#define NO_FLAGS_SET 0

typedef struct {
    char * author;
    char * quote;
    char * time;
}quote_t;

int main()
{
    int i;
    list_t * l1=list_new();
        dataBase * db = createNewDatabase(FILE_NAME);
        musician_t *t1 = malloc(sizeof(struct musician_s));
        t1->id=6;
        strcpy(t1->name, "Donkey");
        strcpy(t1->surname, "Kong");
        t1->salary = 10000.50;
        t1->instr = 2;
        strcpy(t1->birthDate, "1961.01.01");
        //create_musician(db, t1);
        //delete_musician(db,6);
        int cnt=count_musicians(db);
        printf("Musicians count : %i\n", cnt);
        get_AllMusician(db, l1);
        for(i=0;i<l1->count;i++){
            if(l1->arr[i]!=NULL){
                musician_print(l1->arr[i]);
            }
        }
    //musician_print(get_musician(db,1));
    list_t * l2=list_new();
    select_musicians(db,l2,2,15000.0, 21);
    for(i=0;i<l2->count;i++){
            if(l2->arr[i]!=NULL){
                musician_print(l1->arr[i]);
            }
    }
    char * str=musiciansToString(l2);//musicianToString(t1);
    printf("%s", str);
    list_free(l1);
    list_free(l2);
    free(t1);
    free(str);
    http_request_startServer(db);
    deleteDatabase(db);
    return 0;
}
