#include <math.h>
int satisfies(int a, int b, int c)
{
    int result;
    if (a<0&&b<0&&c<0)
    {
        int modmin;
        int sum2;
        modmin=fabs(a);
        if (fabs(b)>modmin)
            modmin=fabs(b);
        if (fabs(c)>modmin)
            modmin=fabs(c);
        sum2=a+b+c+modmin;
        if (sum2<(-256)&&modmin == (1 && 2 && 4 && 8 && 16 && 32 && 64 && 128))
            result=1;
        else if (fabs(sum2)-modmin<16||fabs(sum2)<16)
            result=1;
        else
            result=0;
    }
    if (a>=0&&b>=0&&c<0&&c>(-256))
        result=1;
    else
        result=0;
    if(a>=0&&b<0&&c>=0&&b>(-256))
        result=1;
    else
        result=0;
    if(a<0&&b>=0&c>=0&&a>(-256))
        result=1;
    else
        result=0;
    if (a<0&&b<0&&c>=0&&10*(a+b)>(-256))
        result=1;
    else
        result=0;
    if (a<0&&b>=0&&c<0&&10*(a+c)>(-256))
        result=1;
    else
        result=0;
    if (a>=0&&b<0&&c<0&&10*(c+b)>(-256))
        result=1;
    else
        result=0;
    if (a>=0&&b>=0&&c>=0)
    {
        int min;
        int max;
        if (a>b && a>c) max=a;
        else
            if (b>a && b>c) max=b;
            else
                max=c;
        if (a<b && a<c) min=a;
        else
            if (b<a && b<c) min=b;
            else
                min=c;
                if (pow(max,min)<(pow(2,15)-1))
                    result=1;
                    else
                    result=0;
    }
    return result;
}
