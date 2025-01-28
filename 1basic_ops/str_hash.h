#include <math.h>
int strhash(char string[])
{
    int final=0;
    for(int i=strlen(string);i>0;i--)
    {
        final+=(string[i]-'0')*pow(10,strlen(string)-i);
    }
}