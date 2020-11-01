/*
 * Exercise 1-17. Write a program to print all input
 * lines that are longer than 80 characters.
 */
#include <stdio.h>

#define MINLINE 81
#define TABSTOP 8

int main()
{
	char buff[MINLINE];
	int buffsize = 0;
	int linelen = 0;
	int c;

	while ((c=getchar()) != EOF)
	{
		if (c == '\n')
		{
			if (linelen >= MINLINE)
				putchar('\n');
			linelen = 0;
			buffsize = 0;
		}
		else
		{
			if (c == '\t')
				linelen += TABSTOP - (linelen % TABSTOP);
			else
				++linelen;

			if (linelen >= MINLINE)
			{
				if (buffsize != 0)
				{
					buff[buffsize] = '\0';
					printf("%s", buff);
					buffsize = 0;
				}
				putchar(c);
			}
			else
				buff[buffsize++] = c;
		}
	}
	return 0;
}
