#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "cJSON.h"
#include "server_fake.h"

int main()
{
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
        if(strcmp(cmd,"GET /info")==0){
           server_printOwner(server);
            a++;
            break;
        }
        if (0==a){
            printf("unknown comand, try again");
            Sleep(2000);
            system("cls");
        }
	 }
    server_free(server);
    return 0;
}
