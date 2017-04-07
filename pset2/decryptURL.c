// decrypts uggcf:// lbhgh.or/bUt5FWLEUN0 for CS50x Week 2 continued

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    // difference from https
    char charh = 'h';
    int inth = (int)charh;
    printf("%i\n",inth);
    printf("%c\n",argv[1][0]); // print first character of second argument
    int int1 = (int)argv[1][0]; // converts first character of second argument to int
    printf("%i\n",int1); // print int of first character of second argument
    int diff = int1-inth;
    printf("%i\n",diff);
    int lengStr = strlen(argv[1]);
    
    for (int n = 0; n < lengStr; n++)
    {
        
        int intE = (int)argv[1][n];
        int intD = intE - diff;
        char charD = (char)intD;
        printf("%c",charD);
    }
    
    printf("\n");
}
