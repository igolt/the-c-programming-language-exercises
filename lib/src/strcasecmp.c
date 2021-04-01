#include "strlib.h"

#include <ctype.h>

int strcasecmp(const char *s1, const char *s2)
{
  unsigned char c1;
  unsigned char c2;

  do
  {
    c1 = tolower(*s1++);
    c2 = tolower(*s2++);
  } while (c1 && c1 == c2);
  return c1 - c2;
}
