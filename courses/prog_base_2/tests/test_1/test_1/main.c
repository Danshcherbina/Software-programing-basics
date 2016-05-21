#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os.h"

int main()
{
    os_t os1=os_new();
    os_regUser(os1);
    os_userEnterOs(os1, 0);
    os_printActiveUsers(os1);
    os_installProg(os1);
    //os_printAllProgs(os1);
    //os_userRunProg(os1, 1, 1);
    //os_printActiveProgsAndUsers(os1);
    os_free(os1);
    return 0;
}
