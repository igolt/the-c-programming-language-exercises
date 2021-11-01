/*
 * Exercise 1-16. Revise the main routine of the longest-line program so it
 * will correctly print the length of arbitrary long input lines, and as much
 * as possible of the text.
 */
#include <cbook/iolib.h>
#include <stdio.h>

#define MAXLINE 1000

char *copy(char *, const char *);

int
main(void)
{
  char line[MAXLINE], longest[MAXLINE];
  int max = 0;
  int len;

  while ((len = getline(line, MAXLINE)) >= 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }
  if (max > 0) {
    printf("Longest line: \"%s\"\n"
           "Longest line length: %d\n",
           longest, max);
  }
  return 0;
}

char *
copy(char *dest, const char *src)
{
  char *destit = dest;

  while (*src)
    *destit++ = *src++;
  *destit = '\0';
  return dest;
}
