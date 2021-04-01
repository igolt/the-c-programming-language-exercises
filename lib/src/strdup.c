#include "strlib.h"
#include "alloc.h"

#include <string.h>

char *strdup(const char *s)
{
  char *p;

  p = (char *) alloc(strlen(s) + 1);

  if (p != NULL)
    strcpy(p, s);
  return p;
}
