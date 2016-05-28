#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "cJSON.h"
#include "server_fake.h"

int main()
{
    server_t * server = server_new();
    const char cmd[1024];
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
	 while (1){
            int a=0;
        printf("enter your request:\n");
        printf(">>");
        gets(cmd);
         if(strcmp(cmd,"help")==0){
           printf("GET /info - get student info\nexit- exit programm\n");
            a++;
         }
        if(strcmp(cmd,"GET /info")==0){
           server_write(server, jsonString);
            a++;
            break;
        }
        if(strcmp(cmd,"exit")==0){
            system("cls");
           //return EXIT_SUCCESS;
           break;
        }
        if (0==a){
            printf("unknown comand, try again");
            Sleep(2000);
            system("cls");
        }
	 }
	 char response[1024] = "";
	 while (1) {
        const char * request = server_read(server);
        printf("Server> %s\n", request);
        // create response
        strcpy(response, "RESPONSE!");
        server_write(server, response);
    }
    server_free(server);
    return 0;
}
