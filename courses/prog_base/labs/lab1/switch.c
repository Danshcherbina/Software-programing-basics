#include <math.h>
int exec(int op, int a, int b) {
   int result;
   if (op<0){
       int ab=a;
       int ba=b;
       op=-op;
       a=ba;
       b=ab;
    }
    switch(op)
        {
case 0:
    result=-a;
    break;
case 1:
    result=a+b;
    break;
case 2:
    result=a-b;
    break;
case 3:
    result=a*b;
    break;
case 4:
    result=a/b;
    if (b=0||a%b!=0)
        result=0;
    break;
case 5:
    result=fabs(a);
    break;
case 6:
    result=pow(a,b);
    break;
case 7:
case 13:
case 77:
    result=a%b;
    break;
case 8:
    if (a<b)
    result=b;
    if (a>=b)
    result=a;
    break;
case 9:
    if (a<b)
    result=a;
    if (a>=b)
    result=b;
    break;
case 10:
    if (abs(b)%8==0)
    result=abs(a)*sizeof(char);
    if (abs(b)%8==1)
    result=abs(a)*sizeof(signed char);
    if (abs(b)%8==2)
    result=abs(a)*sizeof(short);
    if (abs(b)%8==3)
    result=abs(a)*sizeof(unsigned int);
    if (abs(b)%8==4)
    result=abs(a)*sizeof(long);
    if (abs(b)%8==5)
    result=abs(a)*sizeof(unsigned long long);
    if (abs(b)%8==6)
    result=abs(a)*sizeof(float);
    if (abs(b)%8==7)
    result=abs(a)*sizeof(double);
    break;
case 11:
    if (a==1)
        result=0;
    else
        result=10*cos(b*M_PI)/(a-1);
    break;
default:
    if (op<100)
        result=(op%abs(a+1))+(op%abs(b+1));
        else
        result=-1;
        }
   return result;
}
