/*
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments
 * of type t. (Block structure will help.)
 */

#include <stdio.h>

#define swap(t, x, y) { t __temp__ = x; x = y; y = __temp__; }

void printarray(int array[], size_t size)
{
	size_t i;

	for (i = 0; i < size; ++i)
		printf("%d%c", array[i], (i + 1 == size) ? '\n' : ' ');
}

int main(void)
{
	int array[] = { 10, 20, 30, 40, 50, 60 };
	const size_t arrsize = sizeof(array) / sizeof(*array);

	printarray(array, arrsize);
	swap(int, array[0], array[3]);
	printarray(array, arrsize);

	return 0;
}
