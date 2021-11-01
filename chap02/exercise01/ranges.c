/*
 * Exercise 2-1. Write a program to determine the ranges of
 * char, short, int, and long variables, both signed and unsigned,
 * by printing appropriate values from standard headers and by
 * direct computation. Harder if you compute them: determine the
 * ranges of the various floating-points types.
 */
#include <float.h>
#include <limits.h>
#include <stdio.h>

int
main(void)
{
  puts("VALUES FROM STANDARD HEADERS:");
  printf("unsigned char:  [0, %u]\n", UCHAR_MAX);
  printf("unsigned short: [0, %u]\n", USHRT_MAX);
  printf("unsigned int:   [0, %u]\n", UINT_MAX);
  printf("unsigned long:  [0, %lu]\n\n", ULONG_MAX);

  printf("signed char:  [%d, %d]\n", SCHAR_MIN, SCHAR_MAX);
  printf("signed short: [%hd, %hd]\n", SHRT_MIN, SHRT_MAX);
  printf("signed int:   [%d, %d]\n", INT_MIN, INT_MAX);
  printf("signed long:  [%ld, %ld]\n\n", LONG_MIN, LONG_MAX);

  printf("float: [%f, %f]\n", FLT_MIN, FLT_MAX);
  printf("double: [%g, %g]\n", DBL_MIN, DBL_MAX);
  return 0;
}
