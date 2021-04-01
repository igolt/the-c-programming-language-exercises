/*
 * Exercise 5-1. As written getint treats a + or -
 * not followed by a digit as a valid representation
 * of zero. Fix it to push such a character back on
 * on the input.
 */

#include <stdio.h>
#include <ctype.h>

#define NUM '0'

int getint(int *);

int main(void)
{
	int num;

	while (getint(&num) == NUM)
		printf("%d\n", num);
	return 0;
}

int getch(void);
int ungetch(int);

#define DIG_TO_INT(_c) ((_c) - '0')
#define CONVERT_TO_NUM(_c) \
	(*num = *num * 10 + DIG_TO_INT(_c))

int getint(int *num)
{

	int c;
	char sign = '+';

	/* skip spaces */
	while (isspace(c = getch()))
		;

	/* Verifica se c é uma entrada válida */
	if (!isdigit(c))
	{
		if (!(c == '+' || c == '-'))
		{
			ungetch(c);
			return c;
		}

		/* Verifica se é um sinal seguido de dígito */
		sign = c;
		c = getch();

		if (!isdigit(c))
		{
			ungetch(c);
			ungetch(sign);

			return sign;
		}
	}

	*num = DIG_TO_INT(c);
	while (isdigit(c = getch()))
		CONVERT_TO_NUM(c);
	ungetch(c);

	if (sign == '-')
		*num = -*num;

	return NUM;
}

#define MAX_BUF 100

char buf[MAX_BUF];
size_t bufp = 0;

#define BUF_IS_EMPTY (bufp == 0)
#define BUF_IS_FULL  (bufp == MAX_BUF)

int getch(void)
{
	return (BUF_IS_EMPTY)
		? getchar() : buf[--bufp];
}

int ungetch(int c)
{
	return (BUF_IS_FULL || c == EOF)
		? EOF : (buf[bufp++] = c);
}
