#include <stdio.h>
#include <conio.h>

int seqSum(char s[100],int k, size_t i);
int main()
{
char s[100];
size_t i=0;
int k=0;
int res;
puts("Enter a string:" );
gets(s);
/*for(i=0;s[i]!='\0';i++)
{
    if(s[i]=='.'||s[i]==','|| s[i]=='?'||s[i]=='!'||s[i]==':'||s[i]==';'||s[i]=='-')
    {
        k++;
    }
}*/
res=seqSum(s,k,i);
printf("Number=%d",res);
return 0;
}

int seqSum(char s[100],int k, size_t i){
		if (s[i]=='\0') return k;
		else	{
        if(s[i]=='.'||s[i]==','|| s[i]=='?'||s[i]=='!'||s[i]==':'||s[i]==';'||s[i]=='-')
    {
        k++;
    }
        i++;
        return seqSum(s,k,i);
		}
	}
