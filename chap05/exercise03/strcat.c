/*
 * Exercise 5-3. Write a pointer version of the strcat that we showed
 * int Chapter 2: strcat(s,t) copies the string t to the end of s.
 */

#include <stdio.h>

#define MAXSTR 1000

char *mystrcat(char *, const char *);

int main(void)
{
	char s1[MAXSTR] = "First part";
	const char *s2 = " second part";

	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);

	printf("strcat(s1, s2): %s\n", mystrcat(s1, s2));
	return 0;
}

char *mystrcat(char *s, const char *t)
{
	char *result = s;

	/* find '\0' */
	while (*s)
		++s;

	/* copies t to the end of s */
	while ((*s++ = *t++))
		;
	return result;
}
