/*
 * Exercise 2-5. Write a function any(s1,s2), which return the first
 * location in a string s1 where any character from the string s2 occurs,
 * or -1 if s1 contains no characters from s2. (The standard library function
 * strpbrk does the same job but return a pointer to the location.)
 */
#include <stdio.h>

#include <cbook/iolib.h>

#define MAXLINE 1000

int any(const char *, const char *);

int
main(void)
{
  char s1[MAXLINE], s2[MAXLINE];
  int location;

  while (getline(s1, MAXLINE) >= 0 && getline(s2, MAXLINE) >= 0) {
    printf("s1: \"%s\"\n", s1);
    printf("s2: \"%s\"\n", s2);
    printf("Location: %d\n", (location = any(s1, s2)));
    if (location > 0)
      printf("s1[%d] = '%c'\n", location, s1[location]);
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

int
any(const char *s1, const char *s2)
{
  int i;

  for (i = 0; s1[i]; ++i)
    if (mystrchr(s2, s1[i]))
      return i;
  return -1;
}
