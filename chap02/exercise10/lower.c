/*
 * Exercise 2-10. Rewrite the function lower, which converts upper case
 * letters to lower case, with a conditional expression instead of if-else
 */
#include <stdio.h>

#define MAXLINE 1000

int get_line(char *, int);
int lower(int);
char *strtolower(char *);

int main()
{
	char line[MAXLINE];

	while (get_line(line, MAXLINE) > 0)
		printf("%s", strtolower(line));
	return 0;
}

int get_line(char *line, int max)
{
	int i = 0, c = EOF;

	--max;
	while (i < max && (c=getchar()) != EOF && c != '\n')
		line[i++] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}

int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

char *strtolower(char *s)
{
	int i;

	for (i = 0; s[i]; ++i)
		s[i] = lower(s[i]);
	return s;
}
