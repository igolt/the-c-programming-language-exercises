/*
 * Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 */
#include <cbook/iolib.h>
#include <stdio.h>

#define MAXLINE 1000

void squeeze(char *, const char *);

int
main(void)
{
  char s1[MAXLINE], s2[MAXLINE];

  while (getline(s1, MAXLINE) > 0 && getline(s2, MAXLINE) > 0) {
    squeeze(s1, s2);
    printf("Result: %s\n", s1);
  }
  return 0;
}

int
mystrchr(const char *s, int c)
{
  while (*s)
    if (*s++ == c)
      return 1;
  return 0;
}

void
squeeze(char *s1, const char *s2)
{
  int i, j;

  for (i = j = 0; s1[i]; ++i)
    if (!mystrchr(s2, s1[i]))
      s1[j++] = s1[i];
  s1[j] = '\0';
}
