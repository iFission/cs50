#include <stdio.h>
#include <cs50.h>

int GetPosInt(void);

int main(void)
{
    int height = GetPosInt();
    for (int row = 0; row < height; row++)
    {
        int space = height - row - 1;
        int block = row + 2;
        for (int n = 0; n < space; n++)
        {
            printf(" ");
        }
        for (int n = 0; n < block; n++)
        {
            printf("#");
        }
        printf("\n");
    }
    
}

int GetPosInt(void)
{
    int n;
    do
    {
        printf("Integer from 0 to 23 inclusive.\n");
        n = GetInt();
    }
    while (n<0||n>23);
    return n;
}