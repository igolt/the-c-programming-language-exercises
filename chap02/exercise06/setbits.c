/*
 * Exercise 2-6. Write a function setbits(x,p,n,y) that return x
 * with the n bits that begin at postition p set to the  rightmost
 * n bits of y, leaving the other bits unchanged.
 */
#include <stdio.h>

unsigned setbits(unsigned, unsigned, unsigned, unsigned);

int
main(void)
{
  unsigned x = 2049, p = 10, n = 10, y = 1023;

  printf("x: %u, p: %u, n: %u, y: %u\n", x, p, n, y);
  printf("setbits: %u\n", setbits(x, p, n, y));
  return 0;
}

unsigned
setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
  unsigned mask = ~(~0 << n);

  ++p;
  y = (y & mask) << (p - n);
  x &= ~(mask << (p - n));

  return x | y;
}
