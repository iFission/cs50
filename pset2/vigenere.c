#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // check k is alphabet
        int lenK = strlen(argv[1]); // length of k
        for (int i  = 0; i < lenK; i++)
        {
        	if (!isalpha(argv[1][i]))
            {
                printf("error input\n");
        		return 1;
        	}
        }

        string strP = GetString(); // get plain text
        int i = 0; // ith char in key used

        for (int j = 0; j < strlen(strP); j++) // encrypt each jth char in plain text
        {
        	if (i < lenK) // use a char in key
        	{        		
        		//  find k
        		int k = 0;
        		if (isupper(argv[1][i])) // for caps
        		{
        			k = argv[1][i] - 'A';
        		}
        		else // for small letter
        		{
        			k = argv[1][i] - 'a';
        		}

                // printf("\nk is %i\n", k);
                // printf("\ni is %i\n", i);

        		// encryption
                char c;
                // check char is an alphabet
                if (isalpha(strP[j]))
                {
                    if(isupper(strP[j]))
                    {
                        c = ((strP[j] + k - 'A') % 26 ) + 'A';
                    }
                    else
                    {
                        c = ((strP[j] + k - 'a') % 26 ) + 'a';
                    }
                    i = i + 1;
                }
                else
                {
                    c = strP[j];
                }
                printf("%c",c);
        	}

            if (i >= lenK) // loop key back to first char
            {
                i = i - lenK;
            }

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