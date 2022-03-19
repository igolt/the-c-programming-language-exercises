#ifndef IGOLT_ALLOC_H
#define IGOLT_ALLOC_H

#ifdef USE_CSTD
#include <stdlib.h>

#define alloc(size)  malloc(size)
#define memfree(ptr) free(ptr)
#else
#include <stddef.h>

void *alloc(size_t n);
#define memfree(ptr) do /* Not implemented yet */ while (0);
#endif /* USE_CSTD */

#endif /* IGOLT_ALLOC_H */
