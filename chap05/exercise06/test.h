#ifndef TEST_H
#define TEST_H

#include <stdlib.h>

#define _test_error(expr, line, file)                        \
	printf("%s:%d: Test: `" #expr "` failed.\n", file, line); \
	puts("exiting...");                                        \
	exit(1);

#define test(expr) \
	if (!(expr)) { _test_error(expr, __LINE__, __FILE__) }

#endif /* TEST_H */
