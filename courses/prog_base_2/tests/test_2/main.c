#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sqlite3.h>
#include <winsock2.h>
#include <winsock.h>
#include <time.h>
#include "cJSON.h"
#include "server_fake.h"
#include "musician.h"
#include "list.h"

#define MAXBUFLEN 20480
#define NO_FLAGS_SET 0

typedef struct {
    char * author;
    char * quote;
    char * time;
}quote_t;

int main()
{
    list_t * l1=list_new();
    server_t * server = server_new();
    char * cmd = malloc(100);
    //const char cmd[1024];
    student_t st = {
			.student = "Shcherbina Dan",
			.group = "KP-52",
			.variant=30,
		};
    cJSON * jStudent = cJSON_CreateObject();
    cJSON_AddItemToObject(jStudent, "student", cJSON_CreateString(st.student));
	cJSON_AddItemToObject(jStudent, "group", cJSON_CreateString(st.group));
	cJSON_AddItemToObject(jStudent, "variant", cJSON_CreateNumber(st.variant));
	char * jsonString = cJSON_Print(jStudent);
	server_addOwnerName(server, jsonString);
	 while (1){
            int a=0;
        printf("enter your responce:\n");
        printf(">>");
        gets(cmd);
        if(strcmp(cmd,"/info")==0){
           server_printOwner(server);
            a++;
            break;
        }
        if(strcmp(cmd,"/database")==0){
            int i;
        dataBase * db = createNewDatabase(FILE_NAME);
        int cnt=count_musicians(db);
        printf("Freelansers count : %i\n", cnt);
        for(i=1;i<=cnt;i++){
        list_push_back(l1, get_musician(db, i));
        }
        for(i=0;i<l1->count;i++){
        musician_print(l1->arr[i]);
        }
             cJSON * jArray=cJSON_CreateArray();
             for(i=0;i<l1->count;i++){
             cJSON * jStudent = cJSON_CreateObject();
             cJSON_AddItemToObject(jStudent, "name", cJSON_CreateString(l1->arr[i]->name));
             cJSON_AddItemToObject(jStudent, "surname", cJSON_CreateString(l1->arr[i]->surname));
             cJSON_AddItemToObject(jStudent, "salary", cJSON_CreateNumber(l1->arr[i]->salary));
             cJSON_AddItemToObject(jStudent, "instruments", cJSON_CreateNumber(l1->arr[i]->instr));
             cJSON_AddItemToObject(jStudent, "surname", cJSON_CreateString(l1->arr[i]->birthDate));
             cJSON_AddItemToArray(jArray, jStudent);
             }
             char * jsonString = cJSON_Print(jArray);
             server_setRequest(server, jsonString);
             server_printMsg(server);
             free(jsonString);
             cJSON_Delete(jArray);
             a++;
             break;
        }
        if (0==a){
            printf("unknown comand, try again");
            Sleep(2000);
            system("cls");
        }
	 }
	 /*
	 char buffer[MAXBUFLEN];
	 int numrcv=0;
    SOCKET recvSocket;
    const char * host_name = "pb-homework.appspot.com";
	char request[200];
    sprintf(request, "GET /test/var/30?format=json HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
    int status;
	// Receieve
    numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
	// Print out receieved socket data
    printf("%s\r\n", buffer);

    char * json=strstr(buffer,"{");


    cJSON * SI = cJSON_CreateObject();

    SI=cJSON_Parse(json);


    quote_t * quote=malloc(sizeof(quote_t));

    quote->quote=malloc(strlen(cJSON_GetObjectItem(SI,"quote")->valuestring)+1);
    strcpy(quote->quote,cJSON_GetObjectItem(SI,"quote")->valuestring);

    quote->author = cJSON_GetObjectItem(SI,"author")->valueint;

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    quote->time=malloc(strlen(asctime(timeinfo)));
    strcpy(quote->time,asctime(timeinfo));
    quote->time[strlen(quote->time)-1]='\0';

    cJSON * SM = cJSON_CreateObject();
    cJSON_AddItemToObject(SM, "quote", cJSON_CreateString(quote->quote));
    cJSON_AddItemToObject(SM, "author", cJSON_CreateString(quote->author));
    cJSON_AddItemToObject(SM, "time", cJSON_CreateString(quote->time));
    char * jsonSM = cJSON_Print(SM);



    system("pause");
    server_free(server);*/
    return 0;
}
