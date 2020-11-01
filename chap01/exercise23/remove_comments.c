/*
 * Exercise 1-23. Write a program to remove all comments from a C program. Don't
 * forget to handle double quoted strings and character constants properly.
 * C comments don't nest
 */
#include <stdio.h>

#define TRUE  1
#define FALSE 0

#define ON  1
#define OFF 0

int main()
{
	int c, lastchar = EOF;
	int incomment = FALSE;
	int inchar = FALSE;
	int instr = FALSE;
	int escape = OFF;

	while ((c=getchar()) != EOF)
	{
		if (incomment)
		{
			if (lastchar == '*' && c == '/')
			{
				incomment = FALSE;
				lastchar = EOF;
			}
			else
				lastchar = c;
		}
		else
		{
			if (c == '\\')
				escape = (escape == ON) ? OFF : ON;
			else
			{
				if (instr)
				{
					if (c == '"' && escape == OFF)
						instr = FALSE;
				}
				else if (inchar)
				{
					if (c== '\'' && escape == OFF)
						inchar = FALSE;
				}
				else if (c == '"' && escape == OFF)
					instr = TRUE;
				else if (c== '\'' && escape == OFF)
					inchar = TRUE;
				else if (lastchar == '/' && c == '*')
				{
					incomment = TRUE;
					lastchar = EOF;
				}
				escape = OFF;
			}
			if (lastchar != EOF)
				putchar(lastchar);
			if (!incomment)
				lastchar = c;
		}
	}
	if (lastchar != EOF)
		putchar(lastchar);
	return 0;
}
