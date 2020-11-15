/*
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand
 * notations like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letter of either case and digits, and be prepared
 * to handle cases like a-b-c and a-z0-9 and -a-z. Arrange thta a leading
 * or trailing - is taken literally.
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

char *expand(const char *, char *);
int get_line(char *, int);
int isshorthand(const char *);

int main()
{
	char line[MAXLINE], expanded[MAXLINE];

	while (get_line(line, MAXLINE) > 0)
		printf("%s", expand(line, expanded));
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

int isshorthand(const char *s)
{
	return ((isdigit(*s) && isdigit(*(s + 2))) ||
		(isalpha(*s) && isalpha(*(s + 2)) && !islower(*s) == !islower(*(s + 2)))) &&
		*(s + 1) == '-' && *s < *(s + 2);
}

char *expand(const char *s1, char *s2)
{
	char *expanded = s2;
	char c;

	do
	{
		if (isshorthand(s1))
		{
			do
			{
				c = *s1;
				s1 += 2;

				while (1)
				{
					*s2 = c;

					if (++c > *s1)
						break;
					++s2;
				}
			} while (isshorthand(s1));
		}
		else
			*s2 = *s1;
		++s1;
	} while (*s2++);

	return expanded;
}
