/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat,
 * and strncmp, which operate on at most the first n characters of their
 * argument strings. For example, strncpy(s,t,n) copies at most n characters
 * of t to s.
 */

#include <stdio.h>
#include <string.h>

#define MAX 1000

#define test(format, expr) printf(#expr ": " format "\n", expr);

char *mystrncpy(char *, const char *, size_t);
char *mystrncat(char *, const char *, size_t);
int mystrncmp(const char *, const char *, size_t);

int
main(void)
{
  char str[MAX] = "";

  test("\"%s\"", str);

  test("\"%s\"", mystrncpy(str, "lorem ipsum", 6));
  test("\"%s\"", mystrncat(str, "ipsum blalajsdljaf", 5));
  test("%d", mystrncmp(str, "lorem not ipsum", 6));
  test("%d", mystrncmp(str, "lorem not ipsum", 7));

  return 0;
}

char *
mystrncpy(char *dest, const char *src, size_t n)
{
  char *result = dest;

  for (; n && *src; --n)
    *dest++ = *src++;
  *dest = '\0';
  return result;
}

char *
mystrncat(char *dest, const char *src, size_t n)
{
  /* if there is something to concat */
  if (n && *src)
    mystrncpy(dest + strlen(dest), src, n);
  return dest;
}

int
mystrncmp(const char *s1, const char *s2, size_t n)
{
  for (; n && *s1; --n, ++s1, ++s2)
    if (*s1 != *s2)
      return *s1 - *s2;
  return 0;
}
