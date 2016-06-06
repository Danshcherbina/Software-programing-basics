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

void http_request_startServer(list_t *list){
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
        http_request_chooseMethod(req, clientSocket, list);
        socket_close(clientSocket);
        socket_free(clientSocket);
    }
    socket_close(serverSocket);
    socket_free(serverSocket);
    lib_free();
}

void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, list_t *list){
     if(strcmp(req.method, "OPTIONS") == 0){
        socket_write_string(clientSocket, "HTTP/1.1 200 OK\n"
            "Access-Control-Allow-Origin: *\n"
            "Access-Control-Allow-Methods: DELETE\n"
            "\n");
        return 1;
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
                for(int i = 0; i < list_count(list); i++){
                    sprintf(tempBuff, "%s"
    "<tr>"
		"<th><a href=\"/musicians/%d\">%d</a></th>"
		"<th>%s</th>"
		"<th>%s</th>"
	"</tr>", tempBuff, list_id(list, i), list_id(list, i), list_get(list, i)->name, list_get(list, i)->surname);
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
                    const char * fName = http_request_getArg(&req, "firstName");
                    const char * lName = http_request_getArg(&req, "lastName");
                    const char * pensDate = http_request_getArg(&req, "birthday");
                    double rating = atof(http_request_getArg(&req, "rating"));
                    int  hours = atoi(http_request_getArg(&req, "albumss"));
                    const char * cName = http_request_getArg(&req, "genre");
                    const char * sName = http_request_getArg(&req, "speciality");
                    const char * g1Name = http_request_getArg(&req, "instrument1");
                    const char * g2Name = http_request_getArg(&req, "instrument2");
                    if(!fName || !lName || !pensDate ||
                       !cName || !sName || !g1Name || !g2Name){
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
                            return 1;
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
                            return 1;
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
                            return 1;
                    } else if(strlen(cName) == 0 || strlen(cName) > WORD_LENGTH){
                        char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: invalid genre</p>"
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
                            return 1;
                    } else if(rating < 0 || rating > 10.0){
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
                            return 1;
                    } else if(strlen(sName) == 0 || strlen(sName) > WORD_LENGTH){
                        char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: invalid speciality</p>"
    "</body>"
"</html>");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: text/html\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                    } else if(strlen(g1Name) == 0 || strlen(g1Name) > WORD_LENGTH || strlen(g2Name) == 0 || strlen(g2Name) > WORD_LENGTH){
            char res[MSG_LENGTH];
            sprintf(res,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>MUSICIANS</title>"
    "</head>"
    "<body>"
        "<p>Error: invalid instrument</p>"
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
                            return 1;
                     }else {
                    int this = list_add(list, new_musician());
                    musician_update(list_get(list, list_find_id(list, this)), fName, lName, pensDate, hours, rating, cName, sName, g1Name, g2Name);
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

                                , this);
                        socket_write_string(clientSocket, result);
                        return 1;
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
  "Albums:<br>"
  "<input type=\"text\" name=\"albums\">"
  "<br>"
  "Rating:<br>"
  "<input type=\"text\" name=\"rating\">"
  "<br>"
  "Genre:<br>"
  "<input type=\"text\" name=\"genre\">"
  "<br>"
  "Speciality:<br>"
  "<input type=\"text\" name=\"speciality\">"
  "<br>"
  "Instrument 1:<br>"
  "<input type=\"text\" name=\"instrument1\">"
  "<br>"
  "Instrument 2:<br>"
  "<input type=\"text\" name=\"instrument2\">"
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
                    return 1;
                }
        }else{
        int id = atoi(strtok(req.uri, "/musicians"));
        if(list_find_id(list, id) != -1)
            {
            if(strcmp(req.method, "GET") == 0)
                {
                if(musician_to_message(list_get(list, list_find_id(list, id)), id) != NULL)
                    {
                        char result[BUFFER_LENGTH];
                        musician_t *t = list_get(list, list_find_id(list, id));
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
                "<th>albums:</th>"
                "<th>rating:</th>"
                "<th>genre:</th>"
                "<th>speciality</th>"
                "<th>instrument 1:</th>"
                "<th>instrument 2:</th>"
                "<th>birthday:</th>"
            "</tr>"
            "<tr>"
                "<th>%d</th>"
                "<th>%d</th>"
                "<th>%.2f</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
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
                            , t->name, t->surname,
                             id, t->albums, t->rating, t->genre->name, t->genre->speciality, t->genre->instruments[0],
                             t->genre->instruments[1], t->date, id);
                        socket_write_string(clientSocket, result);
                        return 1;
                    }
                }
                else if(strcmp(req.method, "DELETE") == 0)
                {
                    free_musician(list_remove(list, list_find_id(list, id)));
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
                    return 1;
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
                    return 1;
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
                return 1;
            }

            }
        }
    else if(strcmp(req.uri, "/api")>0){
            if(!strcmp(req.uri, "/api/"))
        {
        char msg[MSG_LENGTH];
        sprintf(msg,
                    "<message>\n"
                    "\t<status>ok</status>\n"
                    "\t<text>HELLO, USER!</text>\n"
                    "</message>\n");
        socket_write_string(clientSocket, msg);
        }
    else
        if (strcmp(req.uri, "/api/musicians") == 0)
        {
            if(strcmp(req.method, "GET") == 0){
                    char result[10000];
                    sprintf(result,
                        "HTTP/1.1 200 OK\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0",
                        strlen(all_musicians_to_message(list)), all_musicians_to_message(list));
                    socket_write_string(clientSocket, result);
                }

            /*  else{
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
            }*/
        }
        if (strcmp(req.uri, "/api/musicians")==0)
        {if(strcmp(req.method, "POST") == 0)
                {
                    char result[MSG_LENGTH];
                    const char * fName = http_request_getArg(&req, "firstName");
                    const char * lName = http_request_getArg(&req, "lastName");
                    const char * pensDate = http_request_getArg(&req, "birthday");
                    double rating = atof(http_request_getArg(&req, "rating"));
                    int  hours = atoi(http_request_getArg(&req, "albums"));
                    const char * cName = http_request_getArg(&req, "genre");
                    const char * sName = http_request_getArg(&req, "speciality");
                    const char * g1Name = http_request_getArg(&req, "instrument1");
                    const char * g2Name = http_request_getArg(&req, "instrument2");
                    if(!fName || !lName || !pensDate ||
                       !cName || !sName || !g1Name || !g2Name){
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
                            return 1;
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
                            return 1;
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
                            return 1;
                    } else if(strlen(cName) == 0 || strlen(cName) > WORD_LENGTH){
                        char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>invalid genre</text>\n"
                            "</message>\n");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            return 1;
                    } else if(rating < 0 || rating > 10.0){
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
                            return 1;
                    } else if(strlen(sName) == 0 || strlen(sName) > WORD_LENGTH){
                        char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>invalid speciality</text>\n"
                            "</message>\n");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                    } else if(strlen(g1Name) == 0 || strlen(g1Name) > WORD_LENGTH || strlen(g2Name) == 0 || strlen(g2Name) > WORD_LENGTH){
            char res[MSG_LENGTH];
            sprintf(res,
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>invalid instrument</text>\n"
                            "</message>\n");
                sprintf(result,
                                "HTTP/1.1 403 ERROR\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                            socket_write_string(clientSocket, result);
                            return 1;
                     }else {
                    int this = list_add(list, new_musician());
                    musician_update(list_get(list, list_find_id(list, this)), fName, lName, pensDate, hours, rating, cName, sName, g1Name, g2Name);
                      printf("New:\n"
                           "<musician>\n"
                            "\t<id>%i</id>\n"
                            "\t<firstName>%s</firstName>\n"
                            "\t<lastName>%s</lastName>\n"
                            "\t<birthday>%s</birthday>\n"
                            "\t<albums>%d</albums>\n"
                            "\t<rating>%.2f</rating>\n"
                            "\t<genre nameGenre=\"%s\">\n"
                            "\t\t<speciality>%s<speciality>\n"
                            "\t\t<instrument1>%s</instrument1>\n"
                            "\t\t<instrument2>%s</instrument2>\n"
                            "\t</genre>\n"
                            "</musician>\n\n",
                            this, fName, lName, pensDate, hours, rating, cName, sName, g1Name, g2Name);
                        char res[MSG_LENGTH];
                        sprintf(res, "<musician>\n"
                            "\t<id>%i</id>\n"
                            "\t<firstName>%s</firstName>\n"
                            "\t<lastName>%s</lastName>\n"
                            "\t<birthday>%s</birthday>\n"
                            "\t<albums>%d</albums>\n"
                            "\t<rating>%.2f</rating>\n"
                            "\t<genre nameGenre=\"%s\">\n"
                            "\t\t<speciality>%s<speciality>\n"
                            "\t\t<instrument1>%s</instrument1>\n"
                            "\t\t<instrument2>%s</instrument2>\n"
                            "\t</genre>\n"
                            "</musician>\n\n",
                               this, fName, lName, pensDate, hours, rating, cName, sName, g1Name, g2Name);
                        sprintf(result,
                                "HTTP/1.1 200 OK\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res);
                        socket_write_string(clientSocket, result);
                        return 1;
                        }
        } else {
        int id = atoi(strtok(req.uri, "/api/musicians"));
        if(list_find_id(list, id) != -1)
            {
            if(strcmp(req.method, "GET") == 0)
                {
                if(musician_to_message(list_get(list, list_find_id(list, id)), id) != NULL)
                    {
                        char result[BUFFER_LENGTH];
                        musician_t *t = list_get(list, list_find_id(list, id));
                        sprintf(result,
                            "HTTP/1.1 200 OK\n"
                            "Content-length: %zu\n"
                            "Content-type: application/xml\n"
                            "\n"
                            "%s\0",
                            strlen(musician_to_message(t, id)), musician_to_message(t, id));
                        socket_write_string(clientSocket, result);
                        return 1;
                    }
                }
                else if(strcmp(req.method, "DELETE") == 0)
                {
                    free_musician(list_remove(list, list_find_id(list, id)));
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg,
                            "<message>\n"
                            "\t<status>ok</status>\n"
                            "\t<text>Musician (id%i) has been deleted</text>\n"
                            "</message>\n", id);
                    socket_write_string(clientSocket, result_msg);
                    return 1;
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
                    return 1;
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
                return 1;
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
                    return 1;
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
            return 1;
    }
}
