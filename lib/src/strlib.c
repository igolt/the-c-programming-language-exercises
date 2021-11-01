#include "strlib.h"
#include "alloc.h"
#include "utils.h"

#include <ctype.h>
#include <string.h>

char *
strdup(const char *s)
{
  char *p;

  p = (char *) alloc(strlen(s) + 1);
  return (p) ? strcpy(p, s) : NULL;
}

int
strcasecmp(const char *s1, const char *s2)
{
  unsigned char c1;
  unsigned char c2;

  do {
    c1 = tolower(*s1++);
    c2 = tolower(*s2++);
  } while (c1 && c1 == c2);
  return c1 - c2;
}

char *
strreverse(char *s)
{
  if (!strempty(s) && s[1]) {
    char *begin = s;
    char *end   = s + strlen(s);

    while (begin < --end)
      SWAP(char, *begin++, *end);
  }
  return s;
}
