/*
 * Exercise 2-3. Write a function htoi(s), which converts a string of
 * hexadecimal digits(including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, 'a' through 'f', and 'A'
 * through 'F'.
 */
#include <ctype.h>
#include <stdio.h>

#include <cbook/iolib.h>

#define MAXLINE 1000

int htoi(const char *);

int
main(void)
{
  char line[MAXLINE];

  while (getline(line, MAXLINE) > 0)
    printf("%d\n", htoi(line));
  return 0;
}

int
htoi(const char *s)
{
  int num = 0;
  int sig = 1;

  if (*s == '-') {
    sig = -1;
    ++s;
  }
  if (*s == '0' && (s[1] == 'x' || s[1] == 'X'))
    s += 2;

  while (isxdigit(*s)) {
    if (isdigit(*s))
      num = num * 16 + (*s - '0');
    else
      num = num * 16 + (tolower(*s) - 'a') + 10;
    ++s;
  }
  return num * sig;
}
