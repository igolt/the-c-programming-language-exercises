#include "quicksort.h"

#include "iolib.h"

#define SWAP(a, b, size)       \
	do                           \
	{                            \
		char *__a = (char *) (a);  \
		char *__b = (char *) (b);  \
		size_t __size = (size);    \
		                           \
		do                         \
		{                          \
		  char temp = *__a;        \
		  *__a++ = *__b;           \
		  *__b++ = temp;           \
		} while (--__size);        \
	} while (0)

void quicksort(void *pbase, size_t nmemb, size_t size, compfunc_t comp)
{
	if (nmemb > 1)
	{
		char *begin = (char *) pbase;
		char *end = begin + (size * nmemb);
		char *it = begin + size;
		char *left_end = begin + (size * (nmemb / 2));
		char *right_begin = it;

		SWAP(left_end, begin, size);

		left_end = begin;

		while (it < end)
		{
			int result = (*comp)(it, begin);

			if (result == 0)
			{
				SWAP(right_begin, it, size);
				right_begin += size;
			}
			else if (result < 0)
			{
				left_end += size;
				if (it != right_begin)
					SWAP(left_end, right_begin, size);
				right_begin += size;
				SWAP(left_end, it, size);
			}
			it += size;
		}

		SWAP(left_end, begin, size);
		
		quicksort(pbase, (left_end - begin) / size, size, comp);
		quicksort((void *) right_begin, (end - right_begin) / size, size, comp);
  }
}
