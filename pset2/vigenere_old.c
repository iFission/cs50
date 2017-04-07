#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // check k is alphabet
        int lenK = strlen(argv[1]); // length of k
        for (int i  = 0; i < lenK; i++)
        {
        	int intKi = (int)argv[1][i]; // variable for each ith char of key
        	
        	if ( (intKi >= 65 && intKi <= 90) || (intKi >= 97 && intKi <= 122) )
        	{

        	}
        	
        	else
        	{
                printf("error input\n");
        		return 1;
        	}
        }
        

        string strP = GetString(); // get plain text
        int intP = strlen(strP); // length of plain text
        int intKi = 0;// variable for each ith char of key
        int i = 0; // ith char in key used
        //  int intCj = 0; // variable for each jth char of encrpyted char

        for (int j = 0; j < intP; j++) // encrypt each jth char in plain text
        {
        	int intPj = (int)strP[j]; // convert jth plain char to int

        	int intCj = 0; // jnt of jth cipher

        	if (i < lenK) // use a char in key
        	{
        		intKi = (int)argv[1][i]; // variable for each ith char of key
        		
        		//  find k
        		int k = 0;
        		if (intKi >64 && intKi < 91) // for caps
        		{
        			k = intKi - 65;
        		}
        		else // for small letter
        		{
        			k = intKi - 97;
        		}

                // printf("k is %i\n", k);

        		// encryption
        		if (intPj >64 && intPj < 91) // for caps
        		{
        		    intCj = intPj+ k; // get int of encrypted char
        		    if (intCj > 90)
        		    {
        		        intCj = intCj - 26;
        		    }
        		    else if (intCj < 65)
        		    {
        		        intCj = intCj + 26;
        		    }
                    i = i + 1;
        		}
        		else if (intPj>96 && intPj< 123) // for small letter
        		{
        		    intCj = intPj+ k; // get int of encrypted char
        		    if (intCj > 122)
        		    {
        		        intCj = intCj - 26;
        		    }
        		    else if (intCj < 97)
        		    {
        		        intCj = intCj + 26;
        		    }
                i = i + 1;
        		}
        		else
        		{
        		    intCj = intPj;
        		}


                char c = (char)intCj;
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