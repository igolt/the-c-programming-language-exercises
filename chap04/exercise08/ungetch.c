/*
 * Exercise 4-8. Suppose that there will never be more than one 
 * character of pushbash. Modify getch and ungetch accordingly.
 */
#include <stdio.h>
#include <assert.h>

int getch(void);
int ungetch(int c);

int main(void)
{
	int c;

	ungetch('c');
	ungetch('a');

	while ((c=getch()) != EOF)
		putchar(c);
	return 0;
}

char buf = EOF;

int getch(void)
{
	if (buf == EOF)
		return getchar();
	{
		int c = buf;
		buf = EOF;
		return c;
	}
}

int ungetch(int c)
{
	if (c == EOF)
		return EOF;
	return (buf = c);
}
