#include <stdio.h>
#include <cs50.h>

int GetPosInt(void);

int main(void)
{
    printf("How many minutes do you take to shower?\n");
    int showerMinute = GetPosInt();
    printf("minutes: %i\n",showerMinute);
    int waterBottle = (showerMinute)*12;
    printf("bottles: %i\n",waterBottle);
    
}

int GetPosInt(void)
{
    int n;
    do
    {
        n = GetInt();
    }
    while (n<1);
    return n;
}