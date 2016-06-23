#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct university_s{
    char * name;
    int fYear;
    int faculityCnt;
    char ** faculityList;
};

university_t * university_new(char * name, int fYear){
    university_t * un=(university_t *)malloc(sizeof(struct university_s));
    un->name=name;
    un->fYear=fYear;
    un->faculityCnt=0;
    un->faculityList=NULL;
    return un;
}

void university_addFac(university_t * self, char * fac){
    self->faculityList=(char**)realloc(self->faculityList,(self->faculityCnt+1)*sizeof(char*));
    self->faculityList[self->faculityCnt++]=strdup(fac);
    return;
}

char * university_inJSon(list_t * self){
    cJSON * jUnArray=cJSON_CreateArray();
    for(int i=0;i<self->count;i++){
        cJSON * jUniversity = cJSON_CreateObject();
        cJSON_AddItemToObject(jUniversity, "name", cJSON_CreateString(self->arr[i]->name));
        cJSON_AddItemToObject(jUniversity, "foundYear", cJSON_CreateNumber(self->arr[i]->fYear));
        cJSON * jFcArray=cJSON_CreateArray();
    }

}

void static university_print(university_t * self){
    int i;
    printf("Name of university:%s. Year of foundation:%i. Facilities:\n", self->name, self->fYear);
    for(i=0;i<self->faculityCnt;i++){
        if(self->faculityList[i]!=NULL){
            printf("%s\n", self->faculityList[i]);
        }
        else printf("No facilities\n");
    }
}

void university_printAll(list_t * self){
    int i;
    for(i=0;i<self->count;i++){
    university_print(self->arr[i]);
    }

}

university_t * university_getBiggest(list_t * self){
    int i;
    int max=0;
    int maxCnt=0;
    for(i=0;i<self->count;i++){
        if(self->arr[i]->faculityCnt>maxCnt){
            max=i;
            maxCnt=self->arr[i]->faculityCnt;
        }
    }
    university_t * um=self->arr[max];
    return um;
}

char * university_getName(university_t * self){
    return self->name;
}


int university_getFYear(university_t * self){
    return self->fYear;
}

int university_getCnt(university_t * self){
    return self->faculityCnt;
}
