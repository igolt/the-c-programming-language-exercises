/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes
 * the rightmost 1-bit in x. Explain why. Use this observation to write a
 * faster version of bitcount.
 */
#include <stdio.h>

int bitcount(unsigned);

int
main(void)
{
  unsigned x = 10;

  printf("number of bits in %u: %d\n", x, bitcount(x));
  return 0;
}

int
bitcount(unsigned x)
{
  int bits;

  for (bits = 0; x != 0; x &= (x - 1))
    ++bits;
  return bits;
}
