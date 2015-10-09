#include <math.h>
double calc(double x, double y, double z) {
   double a;
    if (x<=y||x==-y)
    {
    a= NAN;
    }
    else
    {a=pow(x,y+1)/pow(x-y,1/z);
    a=a+y/(10*fabs(x+y));
    a=a+sqrt(fabs(cos(x)/cos(y)+1));}
   return a;
}
