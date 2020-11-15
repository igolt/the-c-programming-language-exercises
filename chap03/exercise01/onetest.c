/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside.) Write a version with only
 * one test inside the loop and measure the difference in run-time.
 */
#include <stdio.h>

#define ARRAY_SIZE (sizeof(array) / sizeof(*array))

int binsearch(int, int[], int);
void printarray(int [], int);

int main()
{
	int array[] = { 10, 41, 57, 82, 102, 201, 220, 314, 333, 345, 444, 567, 1021, 2000 };
	int val = 1500;

	printf("Array size: %lu\n", ARRAY_SIZE);
	printarray(array, ARRAY_SIZE);
	printf("Searching for value %d\n", val, binsearch(val, array, ARRAY_SIZE));
	return 0;
 }

int binsearch(int val, int v[], int size)
{
	int low, mid, high;

	low = 0;
	high = size - 1;
	mid = (low + high) / 2;

	while (low <= high && val != v[mid])
	{
		if (val < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
		
		mid = (low + high) / 2;
	}
	return (val == v[mid]) ? mid : -1;
}

void printarray(int array[], int size)
{
	int i;

	for (i = 0; i < size; ++i)
		printf("%d%c", array[i], (i == size - 1) ? '\n' : ' ');
}
