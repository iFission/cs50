#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

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
        
        for (int n = 0; n < strlen(strP); n++)
        {
            int intP = (int)strP[n]; // convert plain char to int
            // printf("%i\n",intP);
            int intC;
            // check char is an alphabet
            if (intP >64 && intP < 91) // for caps
            {
                intC = intP + k; // get int of encrypted char
                if (intC > 90)
                {
                    intC = intC - 26;
                }
                else if (intC < 65)
                {
                    intC = intC + 26;
                }
            }
            else if (intP >96 && intP < 123) // for small letter
            {
                intC = intP + k; // get int of encrypted char
                if (intC > 122)
                {
                    intC = intC - 26;
                }
                else if (intC < 97)
                {
                    intC = intC + 26;
                }
            }
            else
            {
                intC = intP;
            }
            
            char c = (char)intC;
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