/*
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define ASSERT(assertion)                                                      \
  do {                                                                         \
    assert(assertion);                                                         \
    puts("Assertion: `" #assertion "': OK");                                   \
  } while (0)

int strend(const char *, const char *);

int
main(void)
{
  ASSERT(strend("This is america", "rica") == 1);
  ASSERT(strend("This is america", "ica") == 1);
  ASSERT(strend("america", "rica") == 1);

  ASSERT(strend("rica", "This is america") == 0);
  ASSERT(strend("This is america", "ric") == 0);
  ASSERT(strend("This is america", "is") == 0);
  ASSERT(strend("rica", "rica chicka") == 0);
  ASSERT(strend("rica", "ric") == 0);

  return 0;
}

int
strend(const char *s, const char *t)
{
  size_t slen, tlen;

  return (*t == '\0' || (tlen = strlen(t)) > (slen = strlen(s)) ||
          strcmp(s + (slen - tlen), t))
             ? 0
             : 1;
}
