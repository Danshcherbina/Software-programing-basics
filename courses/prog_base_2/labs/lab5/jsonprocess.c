#include <stdlib.h>
#include <stdio.h>

#include "cJSON.h"
#include "musician.h"

char * musicianToString(musician_t * self) {
	cJSON * jMusician = cJSON_CreateObject();
	cJSON_AddItemToObject(jMusician, "id", cJSON_CreateNumber(self->id));
	cJSON_AddItemToObject(jMusician, "name", cJSON_CreateString(self->name));
	cJSON_AddItemToObject(jMusician, "surname", cJSON_CreateString(self->surname));
	cJSON_AddItemToObject(jMusician, "salary", cJSON_CreateNumber(self->salary));
	cJSON_AddItemToObject(jMusician, "instruments", cJSON_CreateNumber(self->instr));
	cJSON_AddItemToObject(jMusician, "birthday", cJSON_CreateString(self->birthDate));
	char * jsonString = cJSON_Print(jMusician);
	cJSON_Delete(jMusician);
	return jsonString;
}

char * musiciansToString(list_t * self) {
    cJSON * jArray=cJSON_CreateArray();
             for(int i=0;i<self->count;i++){
             cJSON * jMusician = cJSON_CreateObject();
             cJSON_AddItemToObject(jMusician, "id", cJSON_CreateNumber(self->arr[i]->id));
             cJSON_AddItemToObject(jMusician, "name", cJSON_CreateString(self->arr[i]->name));
             cJSON_AddItemToObject(jMusician, "surname", cJSON_CreateString(self->arr[i]->surname));
             cJSON_AddItemToObject(jMusician, "salary", cJSON_CreateNumber(self->arr[i]->salary));
             cJSON_AddItemToObject(jMusician, "instruments", cJSON_CreateNumber(self->arr[i]->instr));
             cJSON_AddItemToObject(jMusician, "birthday", cJSON_CreateString(self->arr[i]->birthDate));
             cJSON_AddItemToArray(jArray, jMusician);
             }
             char * jsonString = cJSON_Print(jArray);
             cJSON_Delete(jArray);
             return jsonString;

}
