#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "client.h"
#include "server.h"

static void new_oneValue_NumberOneValue(void **state)
{
    int theValue= 1;
    server_t serverT = Server_new(theValue);
    assert_int_equal(Server_getIndex(serverT), theValue);
    Server_free(serverT);
}

static void crtClient_void_NumberAndClientNumberValueOne(void **state)
{
    int theValue= 1;
    server_t serverT = Server_new(theValue);
    Server_crtClient(serverT);
    assert_int_equal(Server_getClientCnt(serverT), theValue);
    assert_int_equal(Client_getNumber(serverT->clientList[0]), theValue);
    Server_free(serverT);
}

static void sendMessage_void_ClientTwoMsgCountOne(void **state)
{
    char line[100]="Hi";
    int theValue= 1;
    server_t serverT = Server_new(theValue);
    Server_crtClient(serverT);
    Server_crtClient(serverT);
    Client_sendMessage(serverT->clientList[0],serverT->clientList[1], line);
    assert_int_equal(Client_getMessageCount(serverT->clientList[1]), theValue);
    Server_free(serverT);
}

int main()
{
    server_t test=Server_new(1);
    Server_crtClient(test);
    Server_crtClient(test);
    Server_printInfo(test);
    Server_sendMsg(test, 2, 1);
    Server_sendMsg(test, 2, 1);
    Client_printMessages(test->clientList[0]);
    Server_free(test);

    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_oneValue_NumberOneValue),
        cmocka_unit_test(crtClient_void_NumberAndClientNumberValueOne),
        cmocka_unit_test(sendMessage_void_ClientTwoMsgCountOne),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
    return 0;
}
