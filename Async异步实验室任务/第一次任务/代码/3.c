#include <stdio.h>
#include <math.h>

int prime(int);
void prime_n(int);

int main()
{
    int n;
    scanf("%d", &n);
    prime_n(n);
    return 0;
}

int prime(int n)
{
    int i;
    for(i = 2; i < sqrt(n); i++)
    {
        if(!(n % i))
            return 0;
    }
    return 1;
}

void prime_n(int n)
{
    if(n <= 1)
        printf("This is not a prime.\n");
    else if(prime(n))
        printf("This is a prime.\n");
    else
        printf("This is not a prime.\n");
}