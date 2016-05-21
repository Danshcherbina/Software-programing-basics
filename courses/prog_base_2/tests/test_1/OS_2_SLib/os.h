#ifndef OS_H_INCLUDED
#define OS_H_INCLUDED

typedef struct os_s * os_t;
typedef struct program_s * program_t;
typedef struct user_s * user_t;

typedef enum {
    PROG_STOPPED,
    PROG_ACTIVE
} program_type_t;

typedef enum {
    USER_UNACTIVE,
    USER_ACTIVE,
} user_type_t;

os_t os_new();
void user_free(user_t this);
void prog_free(program_t this);
void os_free(os_t this);
user_t user_new(int userId);
void os_regUser(os_t this);
void os_userEnterOs(os_t this, int userInd);
void os_userExitOs(os_t this, int userInd);
void os_printActiveUsers(os_t this);
void os_installProg(os_t this);
void os_printAllProgs(os_t this);
void os_userRunProg(os_t this, int userId, int progInd);
void os_endProg(os_t this,int progInd);
void os_printActiveProgsAndUsers(os_t this);

#endif // OS_H_INCLUDED
