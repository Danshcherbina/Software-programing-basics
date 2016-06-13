#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "musician.h"
#include "socket.h"

typedef struct keyvalue_s keyvalue_t;
typedef struct http_request_s http_request_t;

http_request_t
http_request_parse(const char * const request);

const char *
http_request_getArg(http_request_t * self, const char * key);

const char *
keyvalue_toString(keyvalue_t * self);

void http_request_startServer(dataBase * db);
void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, dataBase * db);

#endif // SERVER_H_INCLUDED
