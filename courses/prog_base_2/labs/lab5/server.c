#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "server.h"
struct keyvalue_s{
    char key[256];
    char value[256];
};

struct http_request_s{
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
};

int checkDate(char *date){
    if(strlen(date) != 10){
        return 0;
    }
    for(int i = 0; i < 10; i++){
        if(i == 2 || i == 5){
            if(date[i] != '.'){
                return 0;
            }
        } else {
            if(!isdigit(date[i]))
                return 0;
        }
    }
    return 1;
}

http_request_t
http_request_parse(const char * const request) {
    http_request_t req;
    req.form = NULL;
    req.formLength = 0;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    // parse form data
    const char * bodyStartPtr = strstr(request, "\r\n\r\n") + strlen("\r\n\r\n");
    const char * cur = bodyStartPtr;
    const char * pairEndPtr = cur;
    const char * eqPtr = cur;
    while (strlen(cur) > 0) {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr) {
            pairEndPtr = cur + strlen(cur);
        }
        keyvalue_t kv;
        // get key
        eqPtr = strchr(cur, '=');
        ptrdiff_t keyLen = eqPtr - cur;
        memcpy(kv.key, cur, keyLen);
        kv.key[keyLen] = '\0';
        // get value
        eqPtr++;
        ptrdiff_t valueLen = pairEndPtr - eqPtr;
        memcpy(kv.value, eqPtr, valueLen);
        kv.value[valueLen] = '\0';
        // insert key-value pair into request form list
        req.formLength += 1;
        req.form = realloc(req.form, sizeof(keyvalue_t) * req.formLength);
        req.form[req.formLength - 1] = kv;
        cur = pairEndPtr + ((strlen(pairEndPtr) > 0) ? 1 : 0);
    }
    return req;
}

const char *
http_request_getArg(http_request_t * self, const char * key) {
    for (int i = 0; i < self->formLength; i++) {
        if (strcmp(self->form[i].key, key) == 0) {
            return self->form[i].value;
        }
    }
    return NULL;
}

const char * keyvalue_toString(keyvalue_t * self) {
    char * str = malloc(sizeof(char) * (strlen(self->key) + strlen(self->value) + 2));
    sprintf(str, "%s=%s\0", self->key, self->value);
    return str;
}

void http_request_startServer(dataBase * db){
    int st;
    lib_init();
    socket_t * serverSocket = socket_new();
    st=socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);
    while(1){
        puts("Waiting for connections");
        socket_t * clientSocket = socket_accept(serverSocket);
        puts("New client");
        char buff[BUFFER_LENGTH];
        int readLength = socket_read(clientSocket, buff, BUFFER_LENGTH);
        if(readLength == 0){
            socket_close(clientSocket);
            socket_free(clientSocket);
            puts("Skipping empty request");
            continue;
        }

        printf("Got Request:\n---------------\n%s\n----------------\n", buff);

        http_request_t req = http_request_parse(buff);

        printf("Method: %s\nURI: %s\n", req.method, req.uri);
        puts("Data:");
        for(int i = 0; i < req.formLength; i++){
            char * kvStr = keyvalue_toString(&req.form[i]);
            printf("\t%s\n", kvStr);
            free(kvStr);
        }
        http_request_chooseMethod(req, clientSocket, db);
        socket_close(clientSocket);
        socket_free(clientSocket);
    }
    socket_close(serverSocket);
    socket_free(serverSocket);
    lib_free();
}

void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, dataBase * db){
    list_t * list=list_new();
        get_AllMusician(db, list);
     if(strcmp(req.method, "OPTIONS") == 0){
        socket_write_string(clientSocket, "HTTP/1.1 200 OK\n"
            "Access-Control-Allow-Origin: *\n"
            "Access-Control-Allow-Methods: DELETE\n"
            "\n");
            list_free(list);
            return ;
     }
    if(!strcmp(req.uri, "/"))
        {
        char msg[MSG_LENGTH];
        sprintf(msg,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIAN</title>"
    "</head>"
    "<body>"

            "<h1>MUSICIANS DATABASE</h1>"
            "<p>Welcome user! </p>"
            "<a href=\"/musicians\">All musicians</a>"

    "</body>"
"</html>"
            );
        socket_write_string(clientSocket, msg);
        }
    else
        if (strcmp(req.uri, "/musicians") == 0)
        {
            if(strcmp(req.method, "GET") == 0){
                char tempBuff[MSG_LENGTH];
                sprintf(tempBuff, "<table>"
                        "<caption>OUR BEST</caption>"
        "<tr>"
            "<th>Id</th>"
            "<th>First Name</th>"
            "<th>Last Name</th>"
	"</tr>");
                for(int i = 0; i < list->count; i++){
                    sprintf(tempBuff, "%s"
    "<tr>"
		"<th><a href=\"/musicians/%d\">%d</a></th>"
		"<th>%s</th>"
		"<th>%s</th>"
	"</tr>", tempBuff,list->arr[i]->id , list->arr[i]->id,list->arr[i]->name, list->arr[i]->surname);
                }
                    char result[10000];
                    sprintf(result,
                        "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"

            "<h3>ALL MUSICIANS</h3>"
            "%s"
            "</table>"
            "<br>"
            "<a href=\"/musicians/new\">New person</a>"


    "</body>"
"</html>", tempBuff);
                    socket_write_string(clientSocket, result);
                }

            else {
                char result_msg[MSG_LENGTH];
            char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"
    );
                sprintf(result_msg,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                socket_write_string(clientSocket, result_msg);
            }
        }
    else if (strcmp(req.uri, "/musicians") > 0)
        {if(strcmp(req.method, "POST") == 0)
                {
                    char result[MSG_LENGTH];
                    int  id = atoi(http_request_getArg(&req, "id"));
                    const char * fName = http_request_getArg(&req, "firstName");
                    const char * lName = http_request_getArg(&req, "lastName");
                    const char * pensDate = http_request_getArg(&req, "birthday");
                    double rating = atof(http_request_getArg(&req, "salary"));
                    int  hours = atoi(http_request_getArg(&req, "instruments"));
                    if(!fName || !lName || !pensDate){
                        char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: empty argument</p>"
    "</body>"
"</html>");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                       }
                    else if(strlen(fName) == 0 || strlen(fName) > WORD_LENGTH || strlen(lName) == 0 || strlen(lName) > WORD_LENGTH){
                            char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: invalid name/surname</p>"
    "</body>"
"</html>");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                    } else if(!checkDate(pensDate)){
                        char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: invalid birthday</p>"
    "</body>"
"</html>");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                    } else if(rating < 0){
                        char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: rating</p>"
    "</body>"
"</html>");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                    } else {
                    musician_t *t1 = malloc(sizeof(struct musician_s));
                    t1->id=id;
                    strcpy(t1->name, fName);
                    strcpy(t1->surname, lName);
                    t1->salary = rating;
                    t1->instr = hours;
                    strcpy(t1->birthDate, pensDate);
                    create_musician(db, t1);

                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>ID %d successfully added</p>"
        "<a href=\"/\">Home</a>"
    "</body>"
"</html>"

                                , t1->id);
                        socket_write_string(clientSocket, result);
                        list_free(list);
                        return ;
                        }
                    }
        else if(!strcmp(req.uri, "/musicians/new")){
            if(!strcmp(req.method, "GET")){
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg, "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<h3>New person</h3>"
        "<form action=\"/musicians/\" method=\"POST\">"
  "First name:<br>"
  "<input type=\"text\" name=\"firstName\"><br>"
  "Last name:<br>"
  "<input type=\"text\" name=\"lastName\">"
  "<br>"
  "Birthday:<br>"
  "<input type=\"text\" name=\"birthday\">"
  "<br>"
  "Instruments:<br>"
  "<input type=\"text\" name=\"instruments\">"
  "<br>"
  "Salary:<br>"
  "<input type=\"text\" name=\"salary\">"
  "<br>"
  "Id:<br>"
  "<input type=\"text\" name=\"id\">"
  "<br>"
  "<input type=\"submit\" value=\"Submit\">"
"</form>"

    "<br>"
    "<a href=\"/\">Home</a>"

    "</body>"
"</html>");
                    socket_write_string(clientSocket, result_msg);
                }else {
                    char result_msg[MSG_LENGTH];
            char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>");
                sprintf(result_msg,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                    socket_write_string(clientSocket, result_msg);
                    list_free(list);
                    return ;
                }
        }else{
        int id = atoi(strtok(req.uri, "/musicians"));
        if(list->arr[id] != NULL)
            {
            if(strcmp(req.method, "GET") == 0)
                {
                if(list->arr[id] != NULL)
                    {
                        char result[BUFFER_LENGTH];
                        sprintf(result, "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<h3>%s %s</h3>"
        "<table>"
            "<tr>"
                "<th>ID:</th>"
                "<th>instruments:</th>"
                "<th>salary:</th>"
                "<th>birthday:</th>"
            "</tr>"
            "<tr>"
                "<th>%d</th>"
                "<th>%d</th>"
                "<th>%.2f</th>"
                "<th>%s</th>"
            "</tr>"
        "</table>"
        "<a href=\"#\" onclick=\"doDelete()\">Delete</a>"
        "<br>"
        "<a href=\"/\">Home</a>"
        "<script>"
            "function doDelete() {"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/musicians/%d\", true);"
                "xhttp.send();"
            "}"
        "</script>"
    "</body>"
"</html>"
                            , list->arr[id]->name, list->arr[id]->surname,
                             list->arr[id]->id, list->arr[id]->instr, list->arr[id]->salary, list->arr[id]->birthDate, id);
                        socket_write_string(clientSocket, result);
                        list_free(list);
                        return ;
                    }
                }
                else if(strcmp(req.method, "DELETE") == 0)
                {
                    delete_musician(db,id);
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg,
                            "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>%d successfully deleted</p>"
        "<a href=\"/\">Home</a>"
    "</body>"
"</html>", id);
                    socket_write_string(clientSocket, result_msg);
                    list_free(list);
                    return ;
                }else {
                    char result_msg[MSG_LENGTH];
            char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>");
                sprintf(result_msg,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                    socket_write_string(clientSocket, result_msg);
                    list_free(list);
                    return ;
                }
            }
            else {
                char result_msg[MSG_LENGTH];
                char res[MSG_LENGTH];
                sprintf(res,
                        "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: %d not found</p>"
    "</body>"
"</html>", id);
                sprintf(result_msg,
                                "HTTP/1.1 404 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                socket_write_string(clientSocket, result_msg);
                list_free(list);
                return ;
            }

            }
        }
    else if(strcmp(req.uri, "/api")>0){
            if(!strcmp(req.uri, "/api/"))
        {
        char msg[MSG_LENGTH];
        sprintf(msg,
                    "{\n\n\"message\":{\n"
                    "\"status\":ok,\n"
                    "\"text\":HELLO, USER!,\n}"
                    "\n}");
        socket_write_string(clientSocket, msg);
        return;
        }
    else
        if (strcmp(req.uri, "/api/musicians") == 0)
        {
            if(strcmp(req.method, "GET") == 0){
                    char result[10000];
                    sprintf(result,
                        "HTTP/1.1 200 OK\n"
                        "Content-length: %zu\n"
                        "Content-type: application/json\n"
                        "\n"
                        "%s\0",
                        strlen(musiciansToString(list)), musiciansToString(list));
                    socket_write_string(clientSocket, result);
                    return;
                }
        }
        if (strcmp(req.uri, "/api/musicians")==0)
        {if(strcmp(req.method, "POST") == 0)
                {
                    char result[MSG_LENGTH];
                    int  id = atoi(http_request_getArg(&req, "id"));
                    const char * fName = http_request_getArg(&req, "firstName");
                    const char * lName = http_request_getArg(&req, "lastName");
                    const char * pensDate = http_request_getArg(&req, "birthday");
                    double rating = atof(http_request_getArg(&req, "salary"));
                    int  hours = atoi(http_request_getArg(&req, "instruments"));
                    if(!fName || !lName || !pensDate){
                        char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Empty argument</text>\n"
                            "</message>\n");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                       }
                    else if(strlen(fName) == 0 || strlen(fName) > WORD_LENGTH || strlen(lName) == 0 || strlen(lName) > WORD_LENGTH){
                            char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>invalid name/surname</text>\n"
                            "</message>\n");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                    } else if(!checkDate(pensDate)){
                        char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>invalid birthday</text>\n"
                            "</message>\n");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                    } else if(rating < 0){
                        char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Invalid Rating</text>\n"
                            "</message>\n");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            list_free(list);
                            return ;
                    } else {
                    musician_t *t1 = malloc(sizeof(struct musician_s));
                    t1->id=id;
                    strcpy(t1->name, fName);
                    strcpy(t1->surname, lName);
                    t1->salary = rating;
                    t1->instr = hours;
                    strcpy(t1->birthDate, pensDate);
                    create_musician(db, t1);
                    char * str= musicianToString(t1);
                      printf("New:\n"
                           "%s",
                            str);
                        char res[MSG_LENGTH];
                        sprintf(res,"%s\n",str);
                        sprintf(result,
                                "HTTP/1.1 200 OK\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                        socket_write_string(clientSocket, result);
                        list_free(list);
                        return ;
                        }
        } else {
        int id = atoi(strtok(req.uri, "/api/musicians"));
        if(list->arr[id] != NULL)
            {
            if(strcmp(req.method, "GET") == 0)
                {
                if(list->arr[id] != NULL)
                    {
                        char result[BUFFER_LENGTH];
                        sprintf(result,
                            "HTTP/1.1 200 OK\n"
                            "Content-length: %zu\n"
                            "Content-type: application/xml\n"
                            "\n"
                            "%s\0",
                            strlen(musicianToString(list->arr[id])),musicianToString(list->arr[id]));
                        socket_write_string(clientSocket, result);
                        list_free(list);
                        return ;
                    }
                }
                else if(strcmp(req.method, "DELETE") == 0)
                {
                    delete_musician(db,id);;
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg,
                            "<message>\n"
                            "\t<status>ok</status>\n"
                            "\t<text>Musician (id%i) has been deleted</text>\n"
                            "</message>\n", id);
                    socket_write_string(clientSocket, result_msg);
                    list_free(list);
                    return ;
                }
                else {
                    char result_msg[MSG_LENGTH];
            char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Not Allowed</text>\n"
                            "</message>\n");
                sprintf(result_msg,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                    socket_write_string(clientSocket, result_msg);
                    list_free(list);
                    return ;
                }
           } else {
                char result_msg[MSG_LENGTH];
                char res[MSG_LENGTH];
                sprintf(res,
                        "<message>\n"
                        "\t<status>error</status>\n"
                        "\t<text>Teacher (id%i) not found</text>\n"
                        "</message>\n", id);
                sprintf(result_msg,
                                "HTTP/1.1 404 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                socket_write_string(clientSocket, result_msg);
                list_free(list);
                return ;
            }

        }
        }  else {
                    char result_msg[MSG_LENGTH];
            char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Not Allowed</text>\n"
                            "</message>\n");
                sprintf(result_msg,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                    socket_write_string(clientSocket, result_msg);
                    list_free(list);
                    return ;
                }
        }
        else {
            char result_msg[MSG_LENGTH];
            char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Not Found</text>\n"
                            "</message>\n");
                sprintf(result_msg,
                                "HTTP/1.1 404 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
            socket_write_string(clientSocket, result_msg);
            list_free(list);
            return ;
    }
    list_free(list);
}
