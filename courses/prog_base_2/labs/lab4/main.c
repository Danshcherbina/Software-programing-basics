#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

int main(void){
    char line[100];
    char text[10000] = "";
    FILE * fr = fopen("musicians.xml", "r");
    while(fgets(line, 100, fr)){
    strcat(text, line);
    }
    list_t *teachers = list_new();
    xml_extract(text, teachers);
    xml_out(text);
    http_request_startServer(teachers);
    list_free(teachers);
    return 0;
}
