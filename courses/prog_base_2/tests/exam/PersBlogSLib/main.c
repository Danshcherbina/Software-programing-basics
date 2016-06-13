#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "parking.h"

struct notes_s{
    int reqCount;
    note_act_t reqList[100];
};

struct car_s{
    car_stat_t status;
    char* name;
    int id;
};

struct carOwner_s{
    int id;
    char * name;
    car_t * car;
};

struct group_s{
    int salary;
    int ownerCount;
    carOwner_t * ownersList;
};

struct owners_s{
    int groupCount;
    group_t * groupList;
};

struct parking_s{
    notes_t * notesList;
    owners_t * ownersList;
};

notes_t * notes_new(){
    notes_t * nn=(notes_t *)malloc(sizeof(struct notes_s));
    nn->reqCount=0;
    return nn;
}

parking_t * parking_new(){
    parking_t * pcn=(parking_t *)malloc(sizeof(struct parking_s));
    pcn->notesList=notes_new();
    pcn->ownersList=NULL;
    return pcn;
}

void parking_addNote(parking_t * self, note_act_t stat){
    self->notesList->reqList[self->notesList->reqCount]=stat;
    self->notesList->reqCount++;
}

void parking_getNotes(parking_t * self){
    int incnt=0;
    int outcnt=0;
    printf("Number of notes:%i\n", self->notesList->reqCount);
    for(int i=0;i<self->notesList->reqCount;i++){
        if(self->notesList->reqList[i]==AUTO_IN)
            incnt++;
        if(self->notesList->reqList[i]==AUTO_OUT)
            outcnt++;
    }
    printf("%i cars entered parking\n%i cars escaped parking",incnt, outcnt );
}

