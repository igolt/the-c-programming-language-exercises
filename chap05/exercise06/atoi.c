#include <stdio.h>
#include <ctype.h>

#include "test.h"

int atoi(const char *);

int main(void)
{
	test(5 == atoi("   5"));
	test(5  == atoi("+5"));
	test(-892 == atoi("  -892"));
	test(0 == atoi("   - 892"));
	test(298 == atoi("   +298 765"));
	test(298 != atoi("765"));

	printf("Sucess!!!\n");
	return 0;
}

int atoi(const char *s)
{
	int val;
	char sig;

	while (isspace(*s))
		++s;

	sig = (*s == '-') ? '-' : '+';

	if (*s == '+' || *s == '-')
		++s;

	val = 0;
	while (isdigit(*s))
		val = val * 10 + *s++ - '0';
	return (sig == '-') ? -val : val;
}
