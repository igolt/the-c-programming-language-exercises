#include <math.h>
#include <stdio.h>
#include <ctype.h>

#define MAXOP 100

#define NUMBER '0'
#define MATH   '1'

int getop(char *);

void push(double);
double pop(void);

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
				push(atof(s));
				break;

			case MATH:
				break;

			case '+':
				push(pop() + pop());
				break;

			case '-':
				aux = pop();
				push(pop() - aux);
				break;

			case '*':
				push(pop() * pop());
				break;

			case '/':
				aux = pop();
				if (aux != 0.0)
					push(pop() / aux);
				else
					puts("error: zero divisor\n");
				break;

			case '\n':
				printf("\t%.8g\n", pop());
				break;

			default:
				printf("error: unknown command %s\n", s);
				break;
		}
		printf("s: %s\n", s);
	}
	return 0;
}

int getch(void);
void ungetch(int);

int getop(char *s)
{
	/* Number | Operator | Word | Invalid operator/word */

	while (isspace((*s = getch())))
		/* Do nothing */;
	if ()
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
	if (bufp < BUFSIZE)
		buf[bufp++] = c;
	else
		puts("ungetch: too many characters");
}

#define MAXVAL 100

double stack[MAXVAL];
int sp = 0;

void push(double val)
{
	if (sp < MAXVAL)
		stack[sp++] = val;
	else
		printf("push: stack full, can't push %g\n", val);
}

double pop(void)
{
	if (sp)
		return stack[--sp];
	else
	{
		puts("pop: stack empty");
		return 0.0;
	}
}
