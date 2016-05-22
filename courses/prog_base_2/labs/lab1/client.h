#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

typedef struct client_s{
    int number;
    int messageCount;
    int *sdArray;
    char **msgArray;
} * client_t;
void Client_printMessages(client_t this);
void Client_sendMessage(client_t sender, client_t dest);
void Client_free(client_t this);
int Client_getNumber(client_t this);
int Client_getMessageCount(client_t this);

#endif // CLIENT_H_INCLUDED
