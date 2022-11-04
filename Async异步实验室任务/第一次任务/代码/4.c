#include <stdio.h>

int number(char ch)
{
    if(ch >= '0' && ch <= '9')
        return 1;
    else
        return 0;
}
int main()
{
    char a[10000] = {'\0'};
    gets(a);
    int i;
    int count = 0;
    for(i = 0; i < strlen(a); i++) 
        count += number(a[i]);
    printf("%d", count);
    return 0;
}