/*
 * Exercise 3-6. Write a version of itoa that accepts three arguments
 * instead of two. The third argument is a minimum field width; the
 * converted number must be padded with blanks on the left if necessary to
 * make it wide enough.
 */

#include <stdio.h>

int myabs(int);
int mystrlen(char *);
char *reverse(char *);
char *itoa(int, char *, int);

int
main(void)
{
  int num = 32, min_width = 5;
  char result[30];

  printf("Num: %d\n", num);
  printf("Min width: %d\n", min_width);
  printf("Result: %s\n", itoa(num, result, min_width));

  return 0;
}

int
myabs(int num)
{
  return (num < 0) ? (num * (-1)) : num;
}

int
mystrlen(char *s)
{
  int i;

  for (i = 0; s[i]; ++i)
    /* Do nothing */;
  return i;
}

char *
reverse(char *s)
{
  char temp;
  int i, j;

  for (i = 0, j = mystrlen(s) - 1; i < j; ++i, --j) {
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
  return s;
}

char *
itoa(int num, char *s, int min_width)
{
  char sign;
  int i;

  sign = (num < 0) ? '-' : '+';

  i = 0;
  do {
    s[i++] = '0' + myabs(num % 10);
  } while ((num /= 10));

  if (sign == '-')
    s[i++] = '-';
  while (i < min_width)
    s[i++] = '*';
  s[i] = '\0';

  return reverse(s);
}
