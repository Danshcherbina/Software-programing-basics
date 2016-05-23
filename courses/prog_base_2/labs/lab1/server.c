#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "server.h"


enum errCode{MEMORRY_ERROR=1, INDEX_ERROR }error;

void errorMsg(int errCode){
    switch(errCode){
        case MEMORRY_ERROR:
        printf("Failed to load memory");
        break;
        case INDEX_ERROR:
        printf("Wrong index");
        break;
    }
    exit(1);
}

server_t Server_new(int number){
    server_t sn= (server_t)malloc(sizeof(struct server_s));
    if (sn==NULL)errorMsg(MEMORRY_ERROR);
    sn->number=number;
    sn->clientCount=0;
    sn->clientList=(client_t *)calloc(10, sizeof(struct client_s));
    if (sn->clientList==NULL) errorMsg(MEMORRY_ERROR);
    return sn;
}

client_t Client_new(int number){
    client_t cn=(client_t)malloc(sizeof(struct client_s));
    if (cn==NULL) errorMsg(MEMORRY_ERROR);
    cn->number=number;
    cn->messageCount=0;
    cn->sdArray=NULL;
    cn->msgArray=NULL;
    return cn;
}

void Server_crtClient(server_t this){
    this->clientCount++;
    this->clientList[this->clientCount-1]=Client_new(this->clientCount);
    return;
}

int Server_getIndex(server_t this) {
    return this->number;
}

int Server_getClientCnt(server_t this) {
    return this->clientCount;
}

int Client_getNumber(client_t this){
    return this->number;
}

void Client_free(client_t this){
    int i;
    for(i = 0; i < this->messageCount; i++)
    free(this->msgArray[i]);
    free(this->msgArray);
}

void Server_free(server_t this){
    int i;
    for(i = 0; i < this->clientCount; i++)
    Client_free(this->clientList[i]);
    free(this);
}

void Server_printInfo(server_t this){
    printf("number of server: %i\n",this->number);
    printf("clients of server #%i: %i\n", this->number,this->clientCount);
    return;
}

void Client_printMessages(client_t this){
    int i;
    printf("%i clients messages:\n", this->number);
    for(i=0;i<this->messageCount;i++){
        if (this->msgArray==NULL){
            printf("This client have no messages\n");
            break;
        }
        printf("sender- client #%i: %s\n",this->sdArray[i] , this->msgArray[i]);
    }
}

int Client_getMessageCount(client_t this){
    return this->messageCount;
}

void Client_sendMessage(client_t sender, client_t dest, char line[100]){
    dest->sdArray=(int*)realloc(dest->sdArray,(dest->messageCount+1)*sizeof(int));
    dest->sdArray[dest->messageCount]=sender->number;
    dest->msgArray=(char**)realloc(dest->msgArray,(dest->messageCount+1)*sizeof(char*));
    dest->msgArray[dest->messageCount++]=strdup(line);
}

void Server_sendMsg(server_t this, int senderInd, int destInd){
    if(senderInd>this->clientCount||destInd>this->clientCount||destInd<0||senderInd<0){
        errorMsg(INDEX_ERROR );
    }
    char line[100];
    printf("Enter the message to send:");
    gets(line);
    Client_sendMessage(this->clientList[senderInd-1], this->clientList[destInd-1], line);
}
