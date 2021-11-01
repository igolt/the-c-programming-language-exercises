/*
 * Exercise 4-12. Adapt the ideas of printd to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char *itoa(int, char *);

int
main(void)
{
  char result[100];

  printf("itoa(%d) = %s\n", INT_MIN, itoa(INT_MIN, result));
  return 0;
}

char *
itoa(int n, char *s)
{
  static int i;

  if (n / 10)
    itoa(n / 10, s);
  else {
    i = 0;
    if (n < 0)
      s[i++] = '-';
  }
  s[i++] = abs(n % 10) + '0';
  s[i] = '\0';
  return s;
}
