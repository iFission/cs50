#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int k = atoi(argv[1]);
        // check k is within 26
        if (k > 26)
        {
            k = k%26;
        }
        
        string strP = GetString();// get plain text
        
        for (int i = 0; i < strlen(strP); i++)
        {
            char c;
            // check char is an alphabet
            if (isalpha(strP[i]))
            {
                if(isupper(strP[i]))
                {
                    c = ((strP[i] + k - 'A') % 26 ) + 'A';
                }
                else
                {
                    c = ((strP[i] + k - 'a') % 26 ) + 'a';
                } 
            }
            else
            {
                c = strP[i];
            }
            // printf("%i",intC);
            printf("%c",c);
     }
        printf("\n");
        return 0;
    }
    else
    {
        printf("error input\n");
        return 1;
    }
}