/*
 * Exercise 1-18. Write a program to remove trailing blanks and tabs
 * from each line of input, and to delete entirely blank lines.
 */
#include <stdio.h>
#include <ctype.h>

#define TRUE  1
#define FALSE 0

int main()
{
	int c; 
	int lastblank = '\0'; 
	int hasnoblanks = FALSE;

	while ((c=getchar()) != EOF)
	{
		if (isblank(c))
		{
			if (lastblank == '\0')
				lastblank = c;
		}
		else
		{
			if (c == '\n')
			{
				if (hasnoblanks)
					putchar(c);
				hasnoblanks = FALSE;
			}
			else
			{
				if (lastblank != '\0')
					putchar(lastblank);
				putchar(c);
				hasnoblanks = TRUE;
			}
			lastblank = '\0';
		}
	}
	return 0;
}
