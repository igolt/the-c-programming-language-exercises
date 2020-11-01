/*
 * Exercise 1-24. Write a program to check a C program for rudimentary
 * syntax errors like unmatched parentheses, brackets and braces. Don't forget
 * about quotes, both single and double, escape sequences, and comments.
 * (This program is hard if you do it in full generality.)
 */
#include <stdio.h>

#define UNMATCHED_BRACES        "Unmatched braces \"{}\""
#define UNMATCHED_BRACKETS      "Unmatched brackets \"()\""
#define UNMATCHED_DOUBLE_QUOTES "Unmatched double quotes"
#define UNMATCHED_SINGLE_QUOTES "Unmatched single quotes"
#define UNTERMINATED_COMMENT    "Unterminated comment"

#define ON  1
#define OFF 0

#define TRUE  1
#define FALSE 0

int islinebreak(int c)
{
	return c == '\n' || c == '\v';
}

int main()
{
	const char *error = NULL;
	int c, lastchar = EOF;
	int instr = FALSE;
	int inchar = FALSE;
	int incomment = FALSE;
	int escape = OFF;
	int opbraces = 0;
	int opbrackets = 0;


	while (!error && (c=getchar()) != EOF)
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
		else if (c == '\\')
			escape = (escape == ON) ? OFF : ON;
		else
		{
			if (instr)
			{
				if (islinebreak(c))
					error = UNMATCHED_DOUBLE_QUOTES;
				else if (c == '"' && escape == OFF)
					instr = FALSE;
			}
			else if (inchar)
			{
				if (islinebreak(c))
					error = UNMATCHED_SINGLE_QUOTES;
				else if (c == '\'' && escape == OFF) 
					inchar = FALSE;
			}
			else if (c == '"')
				instr = TRUE;
			else if (c == '\'')
				inchar = TRUE;
			else if (c == '{')
				++opbraces;
			else if (c == '}')
			{
				if (--opbraces < 0)
					error = UNMATCHED_BRACES;
			}
			else if (c == '(')
				++opbrackets;
			else if (c == ')')
			{
				if (--opbrackets < 0)
					error = UNMATCHED_BRACKETS;
			}
			else
			{
				if (lastchar == '/' && c == '*')
				{
					incomment = TRUE;
					lastchar = EOF;
				}
				else
					lastchar = c;
			}
			escape = OFF;
		}
	}

	if (!error)
	{
		if (opbraces)
			error = UNMATCHED_BRACES;
		else if (opbrackets)
			error = UNMATCHED_BRACKETS;
		else if (incomment)
			error = UNTERMINATED_COMMENT;
		else if (instr)
			error = UNMATCHED_DOUBLE_QUOTES;
		else if (inchar)
			error = UNMATCHED_SINGLE_QUOTES;
	}
	if (error)
		printf("error: %s\n", error);
	else
		puts("De boas B)");
	return 0;
}
