#ifndef IGOLT_ALLOC_H
#define IGOLT_ALLOC_H

#include <stddef.h>

/* We dont need to define a union since
 * sizeof(struct header *) + sizeof(size) > sizeof(long) */
typedef struct header {
  struct header *next;
  size_t size; /* number of header units */
} Header;

#ifdef USE_CSTD
#include <stdlib.h>

#define alloc(size)  malloc(size)
#define memfree(ptr) free(ptr)
#else
#include <stddef.h>

void *alloc(size_t n);
void memfree(void *ptr);
#endif /* USE_CSTD */

#endif /* IGOLT_ALLOC_H */
