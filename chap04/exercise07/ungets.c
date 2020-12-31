/**
 * Exercise 4-7. Write a routine ungets(s) that will push back
 * an entire string onto the input. Should ungets know about buf and
 * bufp, or should it just use ungetch?
 */

#include <stdio.h>

void ungets(const char *);
void ungetch(int);
int getch(void);

int main(void)
{

}

#define BUFSIZE 100

char buffer[BUFSIZE];
int bufp = 0;

#define BUFF_IS_FULL (bufp == BUFSIZE)
#define BUFF_IS_EMPTY (bufp == 0)

void ungets(const char *s)
{
	while (!BUFF_IS_FULL && *s)
		ungetch(*s++)
}

void ungetch(int c)
{
	if (BUFF_IS_FULL)
		puts("ungetch: too many characters\n");
	else
		buffer[bufp++] = c;
}

int getch(void)
{
	return (BUFF_IS_EMPTY) ? getchar() : buffer[--bufp];
}
