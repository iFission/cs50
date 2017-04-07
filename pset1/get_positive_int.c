#include <stdio.h>
#include <cs50.h>

int GetPosOddInt();

int main(void)
{
    int n = GetPosOddInt();
    printf("Your number was %i\n", n);
}

int GetPosOddInt(void)
{
    int n;
    do
    {
        printf("Give me an odd positive integer that is less than 10\n");
        n = GetInt();
    }
    while (n==0||n==2||n==4||n==6||n==8||n==10);
    return n;
}