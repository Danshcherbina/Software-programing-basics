#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

typedef struct server_s{
    int number;
    int clientCount;
    client_t * clientList;
} * server_t;
server_t Server_new(int number);
void Server_crtClient(server_t this);
void Server_printInfo(server_t this);
void Server_sendMsg(server_t this, int senderInd, int destInd);
void Server_free(server_t this);
int Server_getIndex(server_t this);
int Server_getClientCnt(server_t this);

#endif // SERVER_H_INCLUDED
