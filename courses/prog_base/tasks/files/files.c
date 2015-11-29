void fprocess(const char * pread, const char * pwrite){

    int a;
    int b;
    int c;
    int count;
    char str[100];
    FILE * fp;
    fp = fopen(pread, "r");
    if (fp == NULL) {
        puts("Error!");
        return;
    }
    for(count = 1; count < 19; count++){
    fgets(str, 10000, fp);
    }

    fscanf(fp, "%i", &a);
    fscanf(fp, "%i", &b);
    fscanf(fp, "%i", &c);
    fclose(fp);
    fp = fopen(pwrite, "w");
    if (fp == NULL) {
        puts("Error opening pwrite!");
        return ;
    }
    if ((a<c+b)&&(b<a+c)&&(c<a+b)&&a>0&&b>0&&c>0)
    fprintf(fp, "true");
    else
    fprintf(fp, "false");

    fclose(fp);

return;
}
