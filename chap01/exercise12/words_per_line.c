/*
 * Exercise 1-12. Write a program that prints its input one
 * word per line.
 */
#include <ctype.h>
#include <stdio.h>

#include <cbook/utils.h>

int
main(void)
{
  int c, last_out = '\n';
  unsigned line = 1;

  while ((c = getchar()) != EOF) {
    if (isblank(c) || c == '\n') {
      if (last_out != '\n')
        putchar((last_out = '\n'));
    } else {
      if (last_out == '\n')
        printf("%u - ", line++);
      putchar((last_out = c));
    }
  }
  return 0;
}
