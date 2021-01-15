/*
 * Exercise 4-5. Add acess to library functions like sin, exp
 * and pow.
 */
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXOP 100

#define NUMBER '0'
#define MATH   '1'

#define eputs(err_msg) (fprintf(stderr, err_msg "\n"))

int getop(char *);

void   stack_push(double);
double stack_pop(void);

int main(void)
{
	int type;
	double aux;
	char s[MAXOP];

	while ((type=getop(s)) != EOF)
	{
		switch (type)
		{
			case NUMBER:
				stack_push(atof(s));
				break;

			case MATH:
				if (strcmp(s, "sin") == 0)
					stack_push(sin(stack_pop()));
				else if (strcmp(s, "cos") == 0)
					stack_push(cos(stack_pop()));
				else if (strcmp(s, "tan") == 0)
					stack_push(tan(stack_pop()));
				else if (strcmp(s, "sqrt") == 0)
					stack_push(sqrt(stack_pop()));
				else if (strcmp(s, "exp") == 0)
					stack_push(exp(stack_pop()));
				else if (strcmp(s, "pow") == 0)
				{
					aux = stack_pop();
					stack_push(pow(stack_pop(), aux));
				}
				else
					fprintf(stderr, "error: invalid mathematical function: %s\n", s);
				break;

			case '+':
				stack_push(stack_pop() + stack_pop());
				break;

			case '-':
				aux = stack_pop();
				stack_push(stack_pop() - aux);
				break;

			case '*':
				stack_push(stack_pop() * stack_pop());
				break;

			case '/':
				aux = stack_pop();
				if (aux != 0.0)
					stack_push(stack_pop() / aux);
				else
					eputs("error: zero divisor");
				break;

			case '\n':
				printf("\t%.8g\n", stack_pop());
				break;

			default:
				fprintf(stderr, "error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

int getch(void);
void ungetch(int);

int getop(char *s)
{
	int c;
	char *it = s;

	/* Number | Operator | Word | Invalid operator/word */
	while (((*it = c = getch())) == ' ' || c == '\t') /* skip white space */
		;
	/* Read a function name */
	if (isalpha(c) || c == '_')
	{
		while (isalnum(*++it = c = getch()) || c == '_')
			;
		ungetch(c);
		*it = '\0';
		return MATH;
	}

	if (c == '-' || c == '+')
		*++it = c = getch();
	/* if not a number */
	if (!isdigit(c) && c != '.' && c != 'e' && c != 'E')
	{
		it[1] = '\0';
		if (it != s)
			ungetch(c);
		return *s;
	}

	while (isdigit(c))
		*++it = c = getch();
	if (c == '.')
		while (isdigit(*++it = c = getch()))
			;
	if (c == 'e' || c == 'E')
	{
		*++it = c = getch();
		if (isdigit(c) || c == '-' || c == '+')
			while (isdigit(*++it = c = getch()))
				;
	}
	*it = '\0';
	ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp == BUFSIZE)
		eputs("ungetch: too many characters");
	else if (c != EOF)
		buf[bufp++] = c;
}

#define MAXVAL 100

double stack[MAXVAL];
int sp = 0;

void stack_push(double val)
{
	if (sp < MAXVAL)
		stack[sp++] = val;
	else
		fprintf(stderr, "stack_push: stack full, can't push %g\n", val);
}

double stack_pop(void)
{
	if (sp)
		return stack[--sp];
	else
	{
		eputs("stack_pop: stack empty");
		return 0.0;
	}
}
