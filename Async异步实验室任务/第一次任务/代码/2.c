#include <stdio.h>
int main()
{
    char arr[10000] = {'\0'};
    gets(arr);
    int i = 0;
    int character = 0, number = 0, blank = 0, others = 0;
    for(i = 0; i < strlen(arr); i++)
    {
        if(arr[i] >= 65 && arr[i] <= 90)
            character++;
        else if(arr[i] >= 97 && arr[i] <= 122)
            character++;
        else if(arr[i] >= 48 && arr[i] <= 57)
            number++;
        else if(arr[i] == ' ')
            blank++;
        else
            others++;
    }
    printf("character:%d\nnumber:%d\nblank:%d\nothers:%d\n", character, number, blank, others);
    return 0;
}