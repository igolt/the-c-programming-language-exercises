/*
 * Exercise 7-2. Write a program that will print arbitrary input in a sensible
 * way. As a minimum, it should print non-graphic characters in octav or
 * hexadecimal according to local custom, and brak long text lines.
 */
#include <ctype.h>
#include <stdio.h>

#define MAX_LENGH    80
#define OCTAL_LENGTH 6

#define inc(lengh, n)                                                          \
  do {                                                                         \
    unsigned __n = (n);                                                        \
                                                                               \
    if ((lengh += __n) > MAX_LENGH) {                                          \
      putchar('\n');                                                           \
      lengh = __n;                                                             \
    }                                                                          \
  } while (0)

int
main(void)
{
  int c;
  unsigned lengh;

  lengh = 0;
  while ((c = getchar()) != EOF) {
    if (isgraph(c)) {
      inc(lengh, 1);
      putchar(c);
    } else {
      inc(lengh, OCTAL_LENGTH);
      printf(" \\%03o ", c);
    }
  }
  return 0;
}
