#include "alloc.h"

#define ALLOCSIZE 10000

char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

#define ALLOC_END (allocbuf + ALLOCSIZE)

void *
alloc(size_t n)
{
  if (allocp + n > ALLOC_END)
    return NULL;
  allocp += n;
  return (void *) (allocp - n);
}
