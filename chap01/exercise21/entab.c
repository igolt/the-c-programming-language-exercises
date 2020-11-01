/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks
 * by the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab. When either a single blanks would
 * suffice to reach a tab stop, which should be given preference?
 */
#include <stdio.h>

#define TABSTOP 8

int main()
{
	int c;
	unsigned int totabstop;
	unsigned int ns = 0;
	unsigned int linelen = 0;

	while ((c=getchar()) != EOF)
	{
		if (c == ' ')
			++ns;
		else
		{
			while (ns > 1 && ns >= (totabstop = TABSTOP - (linelen % TABSTOP)))
			{
				linelen += totabstop;
				ns -= totabstop;
				putchar('\t');
			}
			while (ns)
			{
				++linelen;
				--ns;
				putchar('*');
			}
			if (c == '\n')
				linelen = 0;
			else if (c == '\t')
				linelen += (TABSTOP - (linelen % TABSTOP));
			else
				++linelen;
			putchar(c);
		}
	}
	return 0;
}

