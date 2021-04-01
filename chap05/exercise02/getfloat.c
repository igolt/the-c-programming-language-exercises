/*
 * Exercise 5-2. Write getfloat, the floating-point analog
 * of getint. What type does getfloat return as its function
 * value?
 */

#include <math.h>
#include <stdio.h>
#include <ctype.h>

#define NUM '0'

int getfloat(double *);

int getch(void);
int ungetch(int);

int main(void)
{
	double num;
	int c;

	while (getfloat(&num) == NUM)
		printf("%g\n", num);
	return 0;
}

#define bool signed char
#define true 1
#define false 0

int getfloat(double *num)
{
	int c;
	bool read_num = false;
	char sign = '\0';

	/* skip white spaces */
	while (isspace(c = getch()))
		;

	if (!(isdigit(c) || c == '.'))
	{
		if (!(c == '-' || c == '+'))
		{
			ungetch(c);
			return c;
		}

		sign = c;
		c = getch();

		if (!(isdigit(c) || c == '.'))
		{
			ungetch(c);
			ungetch(sign);
			return sign;
		}
	}

	*num = 0;

	if (isdigit(c))
	{
		read_num = true;

		do
			*num = *num * 10 + c - '0';
		while (isdigit(c = getch()));
	}

	if (c == '.')
	{
		unsigned power;

		if (!isdigit(c = getch()))
		{
			ungetch(c);
			ungetch('.');
			if (sign)
				ungetch(sign);
			c = read_num ? NUM : '.';
			goto error;
		}

		power = 1;
		do
		{
			*num = *num * 10 + c - '0';
			power *= 10;
		} while (isdigit(c = getch()));

		*num /= power;
	}

	if (c == 'e' || c == 'E')
	{
		char e = c;
		char esign = '+';
		int exp;

		if (!isdigit(c = getch()))
		{
			if (!(c == '+' || c == '-'))
			{
				ungetch(c);
				ungetch(e);
				c = NUM;
				goto error;
			}

			esign = c;

			if (!isdigit(c = getch()))
			{
				ungetch(c);
				ungetch(esign);
				ungetch(e);
				c = NUM;
				goto error;
			}
		}

		exp = c - '0';
		while (isdigit(c))
			exp = exp * 10 + c - '0';

		if (esign == '-')
			exp = -exp;

		*num *= pow(10, (esign == '-') ? -exp : exp);
	}

	ungetch(c);
	c = NUM;

error:
	if (sign == '-')
		*num = -*num;
	return c;
}

#define MAX_BUF 100

char buf[MAX_BUF];
char *bufptr = buf;

#define BUF_END (buf + MAX_BUF)

#define BUF_IS_EMPTY (bufptr == buf)
#define BUF_IS_FULL  (bufptr == BUF_END)

#define POP()   (*--bufptr)
#define PUSH(c) (*bufptr++ = (c))

int getch(void)
{
	return (BUF_IS_EMPTY)
		? getchar() : POP();
}

int ungetch(int c)
{
	return (BUF_IS_FULL || c == EOF)
		? EOF : PUSH(c);
}
