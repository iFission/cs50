#include <stdio.h>
#include <cs50.h>
#include <math.h>

float GetPosFloat (void);

int main(void)
{
    float changeFloat = GetPosFloat();    
    // printf("Calculating change for %.2f...\n...\n", changeFloat);
    int changeCent;
    changeCent = round(changeFloat*100);
    // printf("Change in cents (%i)\n", changeCent);
    int coinNum=0;
    int coinNumQuarter=0;
    int coinNumDime=0;
    int coinNumNickel=0;
    int coinNumPenny=0;
    
    while (changeCent>=25) // quarter
    {
        changeCent = changeCent-25;
        coinNum=coinNum+1;
        coinNumQuarter=coinNumQuarter+1;
        // printf("Change in cents (%i)\n", changeCent);
    }
    
    while (changeCent>=10) // dime
    {
        changeCent = changeCent-10;
        coinNum=coinNum+1;
        coinNumDime=coinNumDime+1;
        // printf("Change in cents (%i)\n", changeCent);
    }
    
    while (changeCent>=5) // nickel
    {
        changeCent = changeCent-5;
        coinNum=coinNum+1;
        coinNumNickel=coinNumNickel+1;
        // printf("Change in cents (%i)\n", changeCent);
    }
    
    while (changeCent>=1) // penny
    {
        changeCent = changeCent-1;
        coinNum=coinNum+1;
        coinNumPenny=coinNumPenny+1;
        // printf("Change in cents (%i)\n", changeCent);
    }
    
    // printf("\nTotal number of coins used: %i.\n%i quarters\n%i dimes\n%i nickels\n%i pennies\n", coinNum,coinNumQuarter, coinNumDime, coinNumNickel, coinNumPenny);
    printf("%i\n", coinNum);
    
}

float GetPosFloat(void)
{
    float n;
    do
    {   
        printf("Input number:\n");
        n = GetFloat();
    }
    while (n<0);
    return n;
}