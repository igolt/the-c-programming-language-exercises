/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside.) Write a version with only
 * one test inside the loop and measure the difference in run-time.
 */
#include <stdio.h>

#define ARRAY_SIZE (sizeof(array) / sizeof(*array))

int binsearch(int, int[], int);
void printarray(int[], int);

int
main(void)
{
  int array[] = {10,  41,  57,  82,  102, 201,  220,
                 314, 333, 345, 444, 567, 1021, 2000};
  int val = 1500;
  int index;

  printf("Array size: %lu\n", ARRAY_SIZE);
  printarray(array, ARRAY_SIZE);

  if ((index = binsearch(val, array, ARRAY_SIZE)) == -1)
    printf("Value %d not found\n", val);
  else
    printf("Value %d found at %d\n", val, index);
  return 0;
}

int
binsearch(int val, int v[], int size)
{
  int low, high, mid;

  low = 0;
  high = size - 1;

  while (low <= high) {
    mid = (low + high) / 2;

    if (val == v[mid])
      return mid;
    else if (val > v[mid])
      low = mid + 1;
    else
      high = mid - 1;
  }
  return -1;
}

void
printarray(int array[], int size)
{
  int i;

  for (i = 0; i < size; ++i)
    printf("%d%c", array[i], (i == size - 1) ? '\n' : ' ');
}
