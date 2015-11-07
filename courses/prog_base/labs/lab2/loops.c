double calc(int n, int m){
int i;
int j;
int f=0;
double res1=0;
double result=0;
for (j=1;j<=m;j++){
        f=f+j*j;
        }
for (i=1;i<=n;i++){
        res1=res1+sin((2*M_PI)/(i+1))*cos(f);
        result=result+res1;
    }
return result;
}
