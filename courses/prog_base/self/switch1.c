#include <stdio.h>
#include <stdlib.h>

int main()
{
    int h=2;
    int m=43;
    int code=697;
    float prce;
    if (code>=10&&code<=999)
    {
        switch(code)
        {
case 44:
    prce= 0.77*h*60+0.77*m;
    break;
case 62:
    prce= 0.8*h*60+0.8*m;
    break;
case 32:
    prce= 0.95*h*60+0.95*m;
    break;
case 692:
case 697:
    prce= 1.5*h*60+1.5*m;
    break;
default:
    prce= 1*h*60+1*m;
        }
    printf("%.2f", prce);
    }
    else
    printf("Pomilka");
    return 0;
}
