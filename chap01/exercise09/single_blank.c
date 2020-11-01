/*
 * Exercise 1-9. Write a program to copy its input to its output, replacing 
 * each string of one or more blanks by a single blank.
 */
#include <stdio.h>
#include <ctype.h>

int main()
{
	int c, last_out = EOF;

	while ((c=getchar()) != EOF)
		if (!(isblank(last_out) && isblank(c)))
			putchar((last_out=c));
	return 0;
}
