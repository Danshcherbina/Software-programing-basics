#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


int checknumb(int size, const char * myString);


int main(int argc, char *argv[])
{
    int i,j,v;
    size_t lncnt=0;
    char ss[100];
    char * myString=&ss;
    FILE *file;
    FILE *fp;
    file = fopen(argv[1], "r");
    printf("%s %s\n", argv[1], argv[2]);
    if (file == NULL) {
        puts("Error opening input file!");
        return 0;
    }
    while (! feof(file))
    {
    if (fgetc(file) == '\n')
            lncnt++;
    }
    fseek(file, 0, SEEK_SET);
    int k[lncnt];
    for (i=0;i<=lncnt;i++){
fgets(myString, 100, file);
    j = strlen(myString)-1;
  if(myString[j]=='\n')
    myString[j] = '\0';
    printf("%s\n", myString);
v=strlen(myString);
k[i]=checknumb(v,myString);
printf("max:%i\n", k[i]);
    }
    fp = fopen(argv[2], "w");
    if (fp == NULL) {
        puts("Error opening output file!");
        return 0;
    }
    for (i=0;i<=lncnt;i++){
        if (k[i]==-10){
        fprintf(fp,"no numbers\n");
        }
        else{
    fprintf(fp,"%i\n", k[i]);
        }
    }
    fclose(file);
    fclose(fp);
return 0;
}

int checknumb(int size,const char * myString){
char str[100]="";
int ck;
int j;
int max=-10;
if (size<=0||size>99||size!=strlen(myString)){
    printf("ERROR");
    return -10;
}
        for(j = 0; j <size+1; j++){
            if (myString[j]=='-'){
                str[ck]=myString[j];
                str[ck+1]='\0';
                ck++;
                continue;
            }
            if (isdigit(myString[j])==0){
                    str[0]='\0';
                    ck=0;
                continue;
            }
            else{
            str[ck]=myString[j];
            str[ck+1]='\0';
            ck++;
            if (myString[j+1]=='\0'&&atoi(str)>max){
            max=atoi(str);
            }
            if (atoi(str)>max){
                        max=atoi(str);
                    }
            }
        }
        //printf("%i\n", max); ya tuuuuuuuutttttttttt
return max;
}
