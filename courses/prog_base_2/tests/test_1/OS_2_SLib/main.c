#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "os.h"

struct user_s{
    int userId;
    user_type_t state;
    int progCnt;
};

struct program_s{
    program_type_t state;
    char *name;
    int userId;
    int progInd;
};


struct os_s{
    int userCnt;
    user_t * userList;
    int progCnt;
    program_t * programList;
};

os_t os_new(){
    os_t osn=(os_t)malloc(sizeof(struct os_s));
    osn->userCnt=0;
    osn->progCnt=0;
    osn->userList=(user_t *)calloc(100, sizeof(struct user_s));
    osn->programList=(program_t *)calloc(100, sizeof(struct program_s));
    return osn;
}

void user_free(user_t this){
    free(this);
}

void prog_free(program_t this){
    free(this->name);
    free(this);
}

void os_free(os_t this){
    int i;
    for(i=0;i<this->userCnt;i++){
        user_free(this->userList[i]);
    }

    free(this);
}

user_t user_new(int userId){
    user_t un=(user_t)malloc(sizeof(struct user_s));
    un->userId=userId;
    un->progCnt=0;
    un->state=USER_UNACTIVE;
    return un;
}

void os_regUser(os_t this){
    this->userCnt++;
    this->userList[this->userCnt-1]=user_new(this->userCnt);
}


void os_userEnterOs(os_t this, int userInd){
    if(userInd<0||userInd>=this->userCnt){
        printf("Wrong user index");
        return;
    }
    this->userList[userInd]->state=USER_ACTIVE;
}

void os_userExitOs(os_t this, int userInd){
     if(userInd<0||userInd>=this->userCnt){
        printf("Wrong user index");
        return;
    }
    if(this->userList[userInd]->state==USER_UNACTIVE){
        printf("User is allready offline");
        return;
    }
    this->userList[userInd]->state=USER_UNACTIVE;
}

void os_printActiveUsers(os_t this){
    int i;
    for(i=0;i<this->userCnt;i++){
        if(this->userList[i]->state==USER_ACTIVE){
            printf("user %i is active", i+1);
        }
    }
}

void os_installProg(os_t this){
    this->programList[this->progCnt-1]->name=NULL;
    char line[100];
    this->programList[this->progCnt-1]->name=(char**)realloc(this->programList[this->progCnt-1]->name,(1)*sizeof(char*));
    printf("Enter name of prog:");
    gets(line);
    this->programList[this->progCnt-1]->name[0]=strdup(line);
    this->programList[this->progCnt-1]->state=PROG_STOPPED;
    this->programList[this->progCnt-1]->userId=-1;
    this->progCnt++;
    this->programList[this->progCnt-1]->progInd=this->progCnt;
}

void os_printAllProgs(os_t this){
    int i;
    for(i=0;i<this->progCnt;i++){
        printf("%i program name:",i+1);
        puts(this->programList[i]->name[0]);
    }
}

void os_userRunProg(os_t this, int userId, int progInd){
    if(this->programList[progInd-1]->state==PROG_ACTIVE){
        printf("This program is allready runned");
        return;
    }
    this->userList[userId-1]->progCnt++;
    this->programList[progInd-1]->userId=userId;
    this->programList[progInd-1]->state=PROG_ACTIVE;
}

void os_endProg(os_t this,int progInd){
    if(this->programList[progInd-1]->state==PROG_STOPPED){
        printf("This program is all ready stopped");
        return;
    }
    this->userList[this->programList[progInd-1]->userId-1]->progCnt--;
    this->programList[progInd-1]->userId=-1;
    this->programList[progInd-1]->state=PROG_STOPPED;
}

void os_printActiveProgsAndUsers(os_t this){
    int i;
    for (i=0;i<this->progCnt;i++){
        if(this->programList[i]->state==PROG_ACTIVE){
            printf("active %i program name:",i+1);
            puts(this->programList[i]->name[0]);
            printf("user id(he runned this prog) %i", this->programList[i]->userId);
        }
    }
    return;
}
