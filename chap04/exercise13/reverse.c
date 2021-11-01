/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

#include <cbook/iolib.h>

#define MAXLINE 100

char *reverse(char *);

int
main(void)
{
  char line[MAXLINE];

  while (getline(line, MAXLINE))
    printf("%s\n", reverse(line));
  return 0;
}

void
reverse_helper(char *left, char *right)
{
  if (left < right) {
    char temp = *left;
    *left++ = *right;
    *right-- = temp;
    reverse_helper(left, right);
  }
}

char *
reverse(char *s)
{
  /* if string length is greater than 1 */
  if (*s != 0 && s[1] != 0) {
    char *end;

    for (end = s; *end; ++end)
      ;
    reverse_helper(s, end - 1);
  }
  return s;
}
