#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <stddef.h>

typedef int (*compfunc_t)(const void *, const void *);

void quicksort(void *pbase, size_t nmemb, size_t size, compfunc_t comp);

#endif /* QUICK_SORT_HPP */
