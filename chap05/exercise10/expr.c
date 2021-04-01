/*
 * Exercise 5-10. Write the program expr, which evaluates a reverse
 * Polish expression from the command line, where each operator or
 * operand is a separate argument. For example,
 *
 *   expr 2 3 4 + *
 * evaluates 2 * (3+4).
 */

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

#define ERR_NO_ARGS  1
#define ERR_ZERO_DIV 2
#define ERR_SYNTAX   3

#define STACK_FULL 1

#define NUM '0'

#define eputs(str) (fputs("error: " str "\n", stderr))

int eprintf(const char *, ...);

int eval_arg(const char *);

size_t stack_size(void);
int stack_push(double);
double stack_pop(void);

int main(int argc, char *argv[])
{
	const char *progname = *argv;
	double op2;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s POLISH-EXPR\n", progname);
		exit(ERR_NO_ARGS);
	}

	while (--argc)
	{
		switch (eval_arg(*++argv))
		{
			case NUM:
				stack_push(atof(*argv));
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
				{
					eprintf("%s: zero divisor\n", progname);
					exit(ERR_ZERO_DIV);
				}
				break;

			case '%':
				op2 = stack_pop();
				stack_push(fmod(stack_pop(), op2));
				break;

			default:
				eprintf("%s: invalid argumet `%s'\n", progname, *argv);
				exit(ERR_SYNTAX);
		}
	}
	printf("%g\n", stack_pop());
	printf("stack size: %lu\n", stack_size());
	return 0;
}

int eprintf(const char *fmt, ...)
{
	va_list ap;
	int done;

	fputs("error: ", stderr);

	va_start(ap, fmt);
	done = vfprintf(stderr, fmt, ap);
	va_end(ap);

	return done;
}

int eval_arg(const char *arg)
{
	while (isspace(*arg))
		++arg;

	if (!isdigit(*arg))
	{
		if (!(*arg == '+' || *arg == '-' || *arg == '.'))
			return *arg;

		++arg;

		if (!isdigit(*arg))
			return *--arg;
	}
	return NUM;
}

#define STACK_MAX 1000

double stack[STACK_MAX];
double *stackp = stack;

#define STACK_END (stack + STACK_MAX)

#define STACK_IS_EMPTY (stackp == stack)
#define STACK_IS_FULL  (stackp == STACK_END)

int stack_push(double val)
{
	if (STACK_IS_FULL)
		return STACK_FULL;
	*stackp++ = val;
	return 0;
}

size_t stack_size(void)
{
	return (stackp - stack);
}

double stack_pop(void)
{
	if (STACK_IS_EMPTY)
	{
		eputs("stack_pop: stack is empty");
		return 0.0;
	}
	return *--stackp;
}
