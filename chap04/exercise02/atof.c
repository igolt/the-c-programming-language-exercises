/*
 * Exercise 4-2. Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

double myatof(const char *s);
int myatoi(const char *s);

int main(void)
{
	const char *s = "123.45e-6";

	printf("result: %g\n", myatof(s));
	return 0;
}

int myatoi(const char *s)
{
	int val;
	short int sign;

	while (isspace(*s))
		++s;

	sign = (*s == '-') ? -1 : 1;

	if (*s == '+' || *s == '-')
		++s;

	for (val = 0; isdigit(*s); ++s)
		val = val * 10 + *s - '0';

	return val * sign;
}

double myatof(const char *s)
{
	double val;
	double f;
	short int sign;

	while (isspace(*s))
		++s;

	sign = (*s == '-') ? -1 : 1;

	if (*s == '+' || *s == '-')
		++s;

	for (val = 0.0; isdigit(*s); ++s)
		val = val * 10 + *s - '0';

	if (*s == '.')
		for (f = 0.1, ++s; isdigit(*s); f /= 10, ++s)
			val += (*s - '0') * f;
	
	if (*s == 'e' || *s == 'E')
	{
		++s;
		val *= pow(10, myatoi(s));
	}
	return val * sign;
}
