#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "test.h"

#define MAXSTR 100

char *itoa(int, char *);

int main(void)
{
	char result[MAXSTR];

	test(strcmp("2489", itoa(2489, result)) == 0);
	test(strcmp("0", itoa(0, result)) == 0);
	test(strcmp("9", itoa(9, result)) == 0);
	test(strcmp("-234", itoa(-234, result)) == 0);

	printf("De boas B-)!\n");
	return 0;
}

int myabs(int);
char *reverse(char *);

char *itoa(int val, char *s)
{
	char *it;
	int is_negative = (val < 0);

	it = s;
	do
	{
		*it++ = myabs(val % 10) + '0';
	} while ((val /= 10));


	if (is_negative)
		*it++ = '-';
	*it = '\0';
	return reverse(s);
}

int myabs(int num)
{
	return (num < 0) ? -num : num;
}

