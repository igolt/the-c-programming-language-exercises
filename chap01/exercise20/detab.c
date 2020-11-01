/*
 * Exercise 1-20. Write a program detab that replaces tabs in the input
 * with the proper number of blanks to space to the next tab stop. Assume
 * a fixed set of tab stops, say evey n columns. Should n be a variable or
 * a symbolic parameter?
 */
#include <stdio.h>

#define TABSTOP 8u

int main()
{
	int c;
	unsigned int i;
	unsigned int linelen;
	unsigned int temp;

	linelen = 0;
	while ((c=getchar()) != EOF)
	{
		if (c == '\t')
		{
			temp = TABSTOP - (linelen % TABSTOP);
			linelen += temp;
			for (i = 0; i < temp; ++i)
				putchar('+');
		}
		else
		{
			putchar(c);

			if (c == '\n')
				linelen = 0;
			else
				++linelen;
		}
	}
	return 0;
}
