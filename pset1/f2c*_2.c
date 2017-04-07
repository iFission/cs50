/**
 * f2c.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Converts Fahrenheit to Celsius.
 *
 * Demonstrates arithmetic.
 */

//#include <cs50.h>
#include <stdio.h>

float f2c();

int main(void)
{
    // ask user user for temperature in Fahrenheit
    printf("Temperature in F: ");
    float f = scanf("%f", &f);
    
    // convert F to C
    float c = f2c(f);
    
    // display result to one decimal place
    printf("%.1f F is %.1f C\n", f, c);
}

float f2c(n)
{   
    return 5.0/9*(n-32.0);
}