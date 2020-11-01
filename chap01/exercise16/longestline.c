/*
 * Exercise 1-16. Revise the main routine of the longest-line program so it
 * will correctly print the length of arbitrary long input lines, and as much
 * as possible of the text.
 */
#include <stdio.h>

#define MAXLINE 1000

int get_line(char *, int);
char *copy(char *, const char *);

int main()
{
	char line[MAXLINE], longest[MAXLINE];
	int max = 0;
	int len;

	while ((len=get_line(line, MAXLINE)) >= 0)
	{
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)
	{
		printf(
			"Longest line: \"%s\"\n"
			"Longest line length: %d\n",
			longest,
			max
		);
	}
	return 0;
}

int get_line(char *line, int max)
{
	int i = 0;
	int c;

	--max;
	while (i < max && (c=getchar()) != EOF && c != '\n')
		line[i++] = c;
	return (c == EOF && i == 0) ? -1 : i;
}

char *copy(char *dest, const char *src)
{
	char *destit = dest;

	while (*src)
		*destit++ = *src++;
	*destit = '\0';
	return dest;
}
