/*
 * Exercise 4-1. Write the function strindex(s,t) which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is none.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int mystrlen(const char *s);
int strindex(const char *s, const char *t);

int main(void)
{
	const char *s1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit";

	assert(mystrlen(s1) - 2 == strindex(s1, "it"));
	assert(-1 == strindex(s1, "opa"));
	assert(0 == strindex(s1, "Lorem"));
	assert(-1 == strindex("Lorem", s1));
	return 0;
}	

int strindex(const char *haystack, const char *needle)
{
	int rightmost = -1;
	
	if (*needle)
	{
		int i, j, k;

		for (i = 0; haystack[i]; ++i)
		{
			for (j = 0, k = i; needle[j] && haystack[k] == needle[j]; ++j, ++k)
				/* Do nothing */;
	
			if (needle[j] == '\0')
				rightmost = i;
		}
	}
	return rightmost;
}

int mystrlen(const char *s)
{
	int len;

	for (len = 0; *s; ++s)
		++len;
	return len;
}
