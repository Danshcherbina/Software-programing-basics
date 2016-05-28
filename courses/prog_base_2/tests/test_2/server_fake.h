#ifndef SERVER_FAKE_H_INCLUDED
#define SERVER_FAKE_H_INCLUDED

typedef struct server_s server_t;

typedef struct {
	char * student;
	char * group;
	int variant;
} student_t;

server_t * server_new(void);
void server_free(server_t * self);
const char * server_read(server_t * self);
void server_write(server_t * self, const char * response);
void server_addOwnerName(server_t * self, char * name);
void server_printOwner(server_t * self);
void server_addOwnerName(server_t * self, char * name);
void server_printMsg(server_t * self);
void server_setRequest(server_t * self, char * request);

#endif // SERVER_FAKE_H_INCLUDED
