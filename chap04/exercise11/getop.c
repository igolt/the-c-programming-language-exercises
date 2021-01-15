/*
 * Exercise 4-11. Modify getop so that it doesn't need to use ungetch.
 * Hint: use a internal static variable.
 */

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP  100
#define NUMBER '0'

int getop(char *);
void stack_push(double);
double stack_pop(void);

int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type=getop(s)) != EOF)
	{
		switch (type)
		{
			case NUMBER:
				stack_push(atof(s));
				break;

			case '+':
				stack_push(stack_pop() + stack_pop());
				break;

			case '*':
				stack_push(stack_pop() * stack_pop());
				break;

			case '-':
				op2 = stack_pop();
				stack_push(stack_pop() - op2);
				break;

			case '/':
				op2 = stack_pop();
				if (op2 != 0.0)
					stack_push(stack_pop() / op2);
				else
					puts("error: zero divisor");
				break;

			case '%':
				op2 = stack_pop();
				stack_push(fmod(stack_pop(), op2));
				break;

			case '\n':
				printf("\tResult: %.8g\n", stack_pop());
				break;

			default:
				fprintf(stderr, "error: unknow command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL 100

double stack[MAXVAL];
int sp = 0;

void stack_push(double f)
{
	if (sp < MAXVAL)
		stack[sp++] = f;
	else
		fprintf(stderr, "error: stack full, can't push %g\n", f);
}

double stack_pop(void)
{
	if (sp > 0)
		return stack[--sp];
	else
	{
		fputs("error: stack empty", stderr);
		return 0.0;
	}
}

int getop(char *s)
{
#define ungetch(__c) (save = (__c))
	static int save = EOF;
	size_t i = 0;
	int c;

	if (save == EOF)
		s[i] = c = getchar();
	else
	{
		s[i] = c = save;
		save = EOF;
	}

	while (c == ' ' || c == '\t')
		s[i] = c = getchar();


	if (c == '-' || c == '+')
		s[++i] = c = getchar();
	if (!isdigit(c) && c != '.' && c != 'e' && c != 'E')
	{
		s[++i] = '\0';
		if (i > 1 && c != EOF)
			ungetch(c);
		return s[0];
	}
	
	while (isdigit(c))
		s[++i] = c = getchar();

	if (c == '.')
		while (isdigit(s[++i] = c = getchar()))
			;

	if (c == 'e' || c == 'E')
	{
		s[++i] = c = getchar();
		if (c == '-' || c == '+' || isdigit(c))
			while (isdigit(s[++i] = c = getchar()))
				;
	}
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
