/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

char *reverse(char *);
char *get_line(char *, size_t);

int main()
{
	char line[MAXLINE];

	while (get_line(line, MAXLINE))
		printf("%s\n", reverse(line));
	return 0;
}

char *get_line(char *line, size_t max)
{
	int c;
	char *it = line;

	if (max == 0)
		return NULL;

	while (--max && (c=getchar()) != EOF && c != '\n')
		*it++ = c;
	*it = '\0';
	return (it == line && c == EOF) ? NULL : line;
}

void reverse_helper(char *left, char *right)
{
	if (left < right)
	{
		char temp = *left;
		*left++ = *right;
		*right-- = temp;
		reverse_helper(left, right);
	}
}

char *reverse(char *s)
{
	/* if string length is greater than 1 */
	if (*s != 0 && s[1] != 0)
	{
		char *end;

		for (end = s; *end; ++end)
			;
		reverse_helper(s, end - 1);
	}
	return s;
}

