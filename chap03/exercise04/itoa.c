/*
 * Exercise 3-4. In a two's complement machine, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to
 * -(2^(wordsize - 1)). Explain why not. Modify it to print that value
 *  correctly, regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <string.h>

int myabs(int);
char *reverse(char *);
char *itoa(int, char *);

int
main(void)
{
  char result[100];
  int largest_negative = ~(~0U >> 1);

  printf("Largest negative = %d\n", largest_negative);
  printf("Largest negative = %s\n", itoa(largest_negative, result));
  return 0;
}

int
myabs(int num)
{
  return (num < 0) ? (num * (-1)) : num;
}

char *
reverse(char *s)
{
  char temp;
  int i, j;

  for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
  return s;
}

char *
itoa(int n, char *s)
{
  char sign;
  int i;

  sign = (n < 0) ? '-' : '+';

  i = 0;
  do {
    s[i++] = myabs(n % 10) + '0';
  } while ((n /= 10));
  if (sign == '-')
    s[i++] = '-';
  s[i] = '\0';
  return reverse(s);
}
