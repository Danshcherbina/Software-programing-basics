#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "server.h"

static enum M_STATUS status = M_OK;

return_M_status(){
    return status;
}

struct client_s{
    int number;
    int messageCount;
    int *sdArray;
    char **msgArray;
};

struct server_s{
    int number;
    int clientCount;
    client_t * clientList;
};

server_t Server_new(int number){
    server_t sn= (server_t)malloc(sizeof(struct server_s));
    if (sn==NULL){
            status=M_MEM_ERROR;
            return NULL;
    }
    sn->number=number;
    sn->clientCount=0;
    sn->clientList=(client_t *)calloc(10, sizeof(struct client_s));
    if (sn->clientList==NULL) {
        status=M_MEM_ERROR;
        return NULL;
    }
    status = M_OK;
    return sn;
}

client_t Client_new(int number){
    client_t cn=(client_t)malloc(sizeof(struct client_s));
    if (cn==NULL) {
        status=M_MEM_ERROR;
        return NULL;
    }
    cn->number=number;
    cn->messageCount=0;
    cn->sdArray=NULL;
    cn->msgArray=NULL;
    status = M_OK;
    return cn;
}

void Server_crtClient(server_t this){
    this->clientCount++;
    this->clientList[this->clientCount-1]=Client_new(this->clientCount);
    if(this->clientList[this->clientCount-1]==NULL){
        status=M_ERROR_OPERATION;
        return;
    }
    status = M_OK;
    return;
}

int Server_getIndex(server_t this) {
    status = M_OK;
    return this->number;
}

int Server_getClientCnt(server_t this) {
    status = M_OK;
    return this->clientCount;
}

int Client_getNumber(client_t this){
    status = M_OK;
    return this->number;
}

void Client_free(client_t this){
    int i;
    for(i = 0; i < this->messageCount; i++)
    free(this->msgArray[i]);
    free(this->msgArray);
    status = M_OK;
}

void Server_free(server_t this){
    int i;
    for(i = 0; i < this->clientCount; i++)
    Client_free(this->clientList[i]);
    free(this);
    status = M_OK;
}

void Server_printInfo(server_t this){
    printf("number of server: %i\n",this->number);
    printf("clients of server #%i: %i\n", this->number,this->clientCount);
    status = M_OK;
    return;
}

int Server_getClientNumber(server_t this, int ind){
    if(ind>=this->clientCount||ind<0){
        status=M_ERROR_OPERATION;
        return;
    }
    status = M_OK;
    return Client_getNumber(this->clientList[ind]);
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
    status = M_OK;
}

void Server_printClientMsg(server_t this, int ind){
    if(ind>=this->clientCount||ind<0){
        status=M_ERROR_OPERATION;
        return;
    }
    Client_printMessages(this->clientList[ind]);
    status = M_OK;
    return;
}

int Server_getClientMessageCnt(server_t this, int ind){
    if(ind>=this->clientCount||ind<0){
        status=M_ERROR_OPERATION;
        return;
    }
    int i=Client_getMessageCount(this->clientList[ind]);
    status = M_OK;
    return i;
}

int Client_getMessageCount(client_t this){
    status = M_OK;
    return this->messageCount;
}

void Client_sendMessage(client_t sender, client_t dest, char line[100]){
    dest->sdArray=(int*)realloc(dest->sdArray,(dest->messageCount+1)*sizeof(int));
    dest->sdArray[dest->messageCount]=sender->number;
    dest->msgArray=(char**)realloc(dest->msgArray,(dest->messageCount+1)*sizeof(char*));
    dest->msgArray[dest->messageCount++]=strdup(line);
    status = M_OK;
}

void Server_sendReadyMessage(server_t this, int senderNum, int destNum){
     if(senderNum>this->clientCount||destNum>this->clientCount||destNum<0||senderNum<0){
        status=M_ERROR_OPERATION;
        return;
    }
    char line[100]="Oiiiiiiiiiiii";
    Client_sendMessage(this->clientList[senderNum-1], this->clientList[destNum-1], line);
    status = M_OK;
}

void Server_sendMsg(server_t this, int senderInd, int destInd){
    if(senderInd>this->clientCount||destInd>this->clientCount||destInd<0||senderInd<0){
        status=M_ERROR_OPERATION;
        return;
    }
    char line[100];
    printf("Enter the message to send:");
    gets(line);
    Client_sendMessage(this->clientList[senderInd-1], this->clientList[destInd-1], line);
    status = M_OK;
}
