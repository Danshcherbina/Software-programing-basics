#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

typedef enum M_STATUS {M_OK, M_MEM_ERROR, M_ERROR_OPERATION} M_STATUS;

typedef struct server_s * server_t;
server_t Server_new(int number);
void Server_crtClient(server_t this);
void Server_printInfo(server_t this);
void Server_sendMsg(server_t this, int senderInd, int destInd);
void Server_free(server_t this);
int Server_getIndex(server_t this);
int Server_getClientCnt(server_t this);
void Server_printClientMsg(server_t this, int ind);
int Server_getClientMessageCnt(server_t this, int ind);
int Server_getClientNumber(server_t this, int ind);
void Server_sendReadyMessage(server_t this, int senderNum, int destNum);

#endif // SERVER_H_INCLUDED
