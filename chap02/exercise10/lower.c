/*
 * Exercise 2-10. Rewrite the function lower, which converts upper case
 * letters to lower case, with a conditional expression instead of if-else
 */
#include <stdio.h>

#include <cbook/iolib.h>

#define MAXLINE 1000

int lower(int);
char *strtolower(char *);

int
main()
{
  char line[MAXLINE];

  while (getline(line, MAXLINE) > 0)
    printf("%s", strtolower(line));
  return 0;
}

int
lower(int c)
{
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

char *
strtolower(char *s)
{
  int i;

  for (i = 0; s[i]; ++i)
    s[i] = lower(s[i]);
  return s;
}
