/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Binary search iterative
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n) // inputs(needle, haystack, size)
{
    int valuesS = 0; //start of the array
    int valuesE = n - 1; //end of the array
    int valuesM;

    do
    {
        valuesM = (valuesE + valuesS) / 2; //middle of the array
//      printf("%i %i %i %i\n", valuesS, valuesM, valuesE, values[valuesM]);
        if (values[valuesM] == value)
        {
            return true;
        }

        if (values[valuesM] < value)
        {
            valuesS = valuesM + 1;
        }

        if (values[valuesM] > value)
        {
            valuesE = valuesM - 1;
        }

    }
    while (valuesS <= valuesE);
    
    return false;
}

/**
 * Bubble sort
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int swap = 0; // set swap counter to 0
    do
    {
        swap = 0;
        
        // swaps elements
        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i+1])
                {
                    int temp = values[i];
                    values[i] = values[i+1];
                    values[i+1] = temp;
                    swap = swap + 1;
                }
        }
    }
    while(swap > 0);
/*    for (int i = 0; i < n; ++i)
    {
        printf("%i\n", values[i]);
    }*/
    return;
}