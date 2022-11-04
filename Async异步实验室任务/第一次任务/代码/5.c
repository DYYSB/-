#include <stdio.h>

int factor(int n)
{
    if(n <= 2)
        return n;
    else
        return n * factor(n - 1);
}
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", factor(n));
    return 0;
}