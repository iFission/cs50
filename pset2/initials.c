#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string name = GetString();
    int len = strlen(name);
    char char1 = name[0];
    int int1 = (int)char1;
    
    if (int1 > 64 && int1 < 91)
    {
        printf("%c",char1);
    }
    else
    {
        int int11 = int1 - 32;
        char char11 = (char)int11;
        printf("%c",char11);
    }
    // print first character

    for(int n = 0; n < len; n++)
    {
        char charn = name[n];
        int intn = (int)charn; // convert to int
        if (intn == 32) // check for space
        {
            int o = n + 1; // if space is found, use next char
            char charo = name[o];
            int into = (int)charo;
            if (into > 64 && into < 91)
            {
                printf("%c",charo);
            }
            else
            {
                int intp = into - 32;
                char charp = (char)intp;
                printf("%c",charp);
            }
        }
    
    
    }
    printf("\n");
}