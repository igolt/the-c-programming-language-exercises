/*
 * Exercise 4-3. Given the basic framework, it's strainghtforward to
 * extend the calculator. Add the modulus (%) operator and provisions
 * for negative numbers.
 */

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP  100
#define NUMBER '0'

int getop(char *);
void push(double);
double pop(void);

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
				op2 = atof(s);
				printf("result: %g\n", op2);
				printf("s: %s\n", s);
				push(op2);
				break;

			case '+':
				push(pop() + pop());
				break;

			case '*':
				push(pop() * pop());
				break;

			case '-':
				op2 = pop();
				push(pop() - op2);
				break;

			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					puts("error: zero divisor");
				break;

			case '%':
				op2 = pop();
				push(fmod(pop(), op2));
				break;

			case '\n':
				printf("\t%.8g\n", pop());
				break;

			default:
				printf("error: unknow command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL 100

double stack[MAXVAL];
int sp = 0;

void push(double f)
{
	if (sp < MAXVAL)
		stack[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return stack[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getch(void);
void ungetch(int);

int getop(char *s)
{
	int i = 0, c;

	while ((s[i] = c = getch()) == ' ' || c == '\t')
		/* Do nothing */;


	if (c == '-' || c == '+')
		s[++i] = c = getch();
	if (!isdigit(c) && c != '.' && c != 'e' && c )
	{
		s[++i] = '\0';
		if (i > 1 && c != EOF)
			ungetch(c);
		return s[0];
	}
	
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			/* Do nothing */;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			/* Do nothing */;

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp < BUFSIZE)
		buf[bufp++] = c;
	else
		printf("ungetch: too many characters\n");
}
