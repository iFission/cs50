/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Binary search recursive
 * Returns true if value is in array of n values, else false.
 */

bool binarySearch(int key, int array[], int min, int max);
int findMidPoint(int min, int max);

bool search(int value, int values[], int n) // inputs(needle, haystack, size)
{
	int valuesS = 0; //start of the array
	int valuesE = n - 1; //end of the array
	binarySearch(value, values, valuesS, valuesE);
	return false;
}

bool binarySearch(int key, int array[], int min, int max)
{
	if (max < min)
	{
		return false;
	}
	else
	{
		int midpoint = findMidPoint(min, max);

		if (array[midpoint] < key)
		{
			binarySearch(key, array, midpoint + 1, max);
		}

		else if (array[midpoint] > key)
		{
			binarySearch(key, array, min, midpoint - 1);
		}

		else
		{
			return true;
		}
	}
	return false;
}

int findMidPoint(int min, int max)
{
	int n = (min + max) / 2;
	return n;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    return;
}