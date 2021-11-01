/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the
 * value of the integer x rotated to the right by n positions.
 */
#include <stdio.h>

unsigned rightrot(unsigned, unsigned);

int
main(void)
{
  unsigned x, n;
  x = 4095;
  n = 10;

  printf("rightrot: %u\n", rightrot(x, n));
  return 0;
}

unsigned
rightrot(unsigned x, unsigned n)
{
  unsigned mask = ~(~0U >> 1);
  unsigned i;

  for (i = 0; i < n; ++i)
    x = (x & 1) ? (x >> 1) | mask : x >> 1;
  return x;
}
