#include <string.h>

char * process(char * resultStr,const  char * textLines[],
               int linesNum, char * extraStr) {
    int i;
    char sas1[]="00";
    char *line;
    char *r;
    char *copy1[linesNum];
    int fix[4]={1};
    for(i=0;i<4;i++){
        copy1[i]=" ";
    }
    for(i = 0; i < linesNum; i++) {
        if (strchr(textLines[i],' ')!=NULL){
        strcpy(resultStr, "0 NULL ");
        strcat(resultStr, extraStr);
        return resultStr;
        }
    }
    puts("=== Text ===");
    for(i = 0; i < linesNum; i++) {
        line = textLines[i];
        puts(line);
    }
    puts("vot");
    for(i = 0; i < linesNum; i++) {
        puts("sv");
        puts(copy1[i]);

    }
    puts("on");

    for(i = 0; i < linesNum; i++) {
    strcpy(copy1,textLines);
    r= strtok(copy1, sas1);
    while(r != NULL){
        fix[i]++;
        r = strtok(NULL, sas1);
    }
    }
    for (i=0;i<linesNum; i++){
    printf("%d\n", fix[i]);
    }
    puts("=== Extra string ===");
    puts(extraStr);
    strcpy(resultStr, "Result: ");
    strcat(resultStr, line);
    return resultStr;
}
