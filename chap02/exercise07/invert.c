/*
 * Exercise 2-7. Write a function invert(x,p,n) that returns x with the n
 * bits that begin at position p inverted(i.e., 1 changed into 0 and vice versa),
 * leaving the other bits unchanged.
 */
#include <stdio.h>

unsigned invert(unsigned, unsigned, unsigned);

int main()
{
	unsigned x = 4095, p = 10, n = 5;

	printf("%u\n", invert(x, p, n));
	return 0;
}

unsigned invert(unsigned x, unsigned p, unsigned n)
{
	unsigned mask = ~(~0 << n) << (p + 1 - n);
	
	return ((x & ~mask) | (~x & mask));
}
