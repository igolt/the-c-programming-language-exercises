/*
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a time.
 */
#include <stdio.h>

#define MAXLINE 1000

int mystrlen(const char *s)
{
	int len = 0;

	while (*s++)
		++len;
	return len;
}

char *reverse(char *s)
{
	int ibeg, iend;
	int aux;

	iend = mystrlen(s) - 1;
	for (ibeg = 0; ibeg < iend; ++ibeg, --iend)
	{
		aux = s[ibeg];
		s[ibeg] = s[iend];
		s[iend] = aux;
	}
	return s;
}

int get_line(char *line, int capacity)
{
	int i = 0, c;

	--capacity;
	while (i < capacity && (c=getchar()) != EOF && c != '\n')
		line[i++] = c;
	line[i] = '\0';
	return (c == EOF && i == 0) ? -1 : i;
}

int main()
{
	char line[MAXLINE];

	while (get_line(line, MAXLINE) >= 0)
		puts(reverse(line));
	return 0;
}
