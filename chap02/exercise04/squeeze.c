/*
 * Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 */
#include <stdio.h>

#define MAXLINE 1000

#define TRUE  1
#define FALSE 0

void squeeze(char *, const char *);
int get_line(char *, int);

int main()
{
	char s1[MAXLINE], s2[MAXLINE];

	while (get_line(s1, MAXLINE) > 0 && get_line(s2, MAXLINE) > 0)
	{
		squeeze(s1, s2);
		printf("Result: %s\n", s1);
	}
	return 0;
}

int mystrchr(const char *s, int c)
{
	while (*s)
		if (*s++ == c)
			return TRUE;
	return FALSE;
}

void squeeze(char *s1, const char *s2)
{
	int i, j;

	for (i = j = 0; s1[i]; ++i)
		if (!mystrchr(s2, s1[i]))
			s1[j++] = s1[i];
	s1[j] = '\0';
}

int get_line(char *line, int lim)
{
	int i = 0, c = EOF;

	--lim;
	while (i < lim && (c=getchar()) != EOF && c != '\n')
		line[i++] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}
