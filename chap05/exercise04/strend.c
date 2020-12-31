/*
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>

#define TRUE  1
#define FALSE 0

#define test(s, t)      \
	printf("s: %s\n", s); \
	printf("t: %s\n", t); \
	printf("strend(s,t): %d\n\n", strend(s, t));

int strend(const char *, const char *);

int main(void)
{
	test("This is america", "rica");
	test("This is america", "is");
	test("This is america", "ica");
	test("This is america", "ric");
	test("america", "rica");
	test("rica", "ric");
	test("rica", "rica chicka");
	return 0;
}

int strend(const char *s, const char *t)
{
	const char *sp, *tp;

	for ( ; *s; ++s)
	{
		for (sp = s, tp = t; *tp && *tp == *sp; ++sp, ++tp)
			;

		if (*tp == *sp)
			return TRUE;
	}
	return FALSE;
}
