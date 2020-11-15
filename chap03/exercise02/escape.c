/*
 * Exercise 3-2. Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies
 * the string t to s. Use a switch. Write a function for the other direction
 * as well, converting espace sequences into the real characters.
 */
#include <stdio.h>

#define MAXLINE 1000

int get_line(char *, int);
char *escape(char *, const char *);
char *unescape(char *, const char *);

int main()
{
	char unescaped[MAXLINE], escaped[MAXLINE];

	while (get_line(unescaped, MAXLINE) > 0)
	{
		printf("escape(s,t): %s\n", escape(escaped, unescaped));
		printf("unescape(s,t): %s", unescape(unescaped, escaped));
	}
	return 0;
}

int get_line(char *line, int max)
{
	int c = EOF, i = 0;

	--max;
	while (i < max && (c=getchar()) != EOF)
	{
		line[i++] = c;
		if (c == '\n')
			break;
	}
	line[i] = '\0';
	return i;
}

char *escape(char *s, const char *t)
{
	char *save = s;

	do
	{
		switch (*t)
		{
			case '\n':
				*s++ = '\\';
				*s = 'n';
				break;
			case '\t':
				*s++ = '\\';
				*s = 't';
				break;
			case '\v':
				*s++ = '\\';
				*s = 'v';
				break;
			case '\a':
				*s++ = '\\';
				*s = 'a';
				break;
			case '\b':
				*s++ = '\\';
				*s = 'b';
				break;
			case '\f':
				*s++ = '\\';
				*s = 'f';
				break;
			case '\r':
				*s++ = '\\';
				*s = 'r';
				break;
			default:
				*s = *t;
				break;
		}
		++t;
	} while (*s++);
	return save;
}

char *unescape(char *s, const char *t)
{
	char *save = s;

	do
	{
		switch (*t)
		{
			case '\\':
				switch (*(t + 1))
				{
					case 'a':
						*s = '\a';
						++t;
						break;
					case 'b':
						*s = '\b';
						++t;
						break;
					case 'f':
						*s = '\f';
						++t;
						break;
					case 'n':
						*s = '\n';
						++t;
						break;
					case 'r':
						*s = '\r';
						++t;
						break;
					case 't':
						*s = '\t';
						++t;
						break;
					case 'v':
						*s = '\v';
						++t;
						break;
					default:
						*s = *t;
						break;
				}
				break;
			default:
				*s = *t;
		}
		
		++t;
	} while (*s++);

	return save;
}
