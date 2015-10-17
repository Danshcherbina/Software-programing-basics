#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double long2double(long long);
int main() {
double ll=-4620000000000000000LL;
double result;
//scanf( "%a", &ll );
result = long2double(ll);
printf("%.325llf", result);
return 0;
}

double long2double(long long ll){

long long num1;
int a[64];
int i,ress = 0;
double ste =0;
double result =0;

for(i=0;i<64;i++){
a[i]=0;
}
if (ll<0){
unsigned long long num1 = ll + 9223372036854775808LL;
a[0] = 1;
for(i=63;i>0;i--){
a[i]=num1%2;
num1=num1/2;
}
}
else{
a[0] = 0;

for(i=63;i>0;i--){
a[i]=ll%2;
ll=ll/2;
}
}
for(i=11;i>0;i--){
ste=ste+a[i]*pow(2,11-i);
}

if (ste == 0){
for (i = 12; i < 64; i++){
result = result + a[i] * pow(2, (-i + 11) + (-1022));
}
} else if (ste == 2047){

for(i=63;i>0;i--){

if(a[i]==1){

ress=1;

break;
}
}
result= ress ? NAN : INFINITY;
} else{
for (i = 12; i < 64; i++){
result = result + a[i] * pow(2, (-i + 11) + (ste - 1023));
}
result+= pow(2, (ste - 1023));

}
if(a[0]) result = -result;
return result;

}
