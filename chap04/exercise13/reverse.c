/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

char *reverse(char *);
int get_line(char *, int);

int main()
{
	char line[MAXLINE];

	while (get_line(line, MAXLINE) != EOF)
		printf("%s\n", reverse(line));
	return 0;
}

int get_line(char *line, int max)
{
	int c, i;

	i = 0;
	--max;
	while (i < max && (c=getchar()) != EOF && c != '\n')
		line[i++] = c;
	line[i] = '\0';
	return (i == 0 && c == EOF) ? EOF : i;
}

char *reverse(char *s)
{
	size_t i;
	size_t j = strlen(s);

	if (j > 1)
	{
		for (i = 0, --j; i < j; ++i, --j)
		{
			char temp = s[i];
			s[i] = s[j];
			s[j] = temp;
		}
	}
	return s;
}
