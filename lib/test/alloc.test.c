#include <stdio.h>

#include "alloc.h"

int main(void)
{
	void *ptr;

	ptr = alloc(10);

	printf("%p\n", ptr);

	return 0;
}
