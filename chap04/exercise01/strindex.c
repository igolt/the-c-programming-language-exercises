/*
 * Exercise 4-1. Write the function strindex(s,t) which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is none.
 */

#include <stdio.h>
#include <stdlib.h>

#define dprint(format, expr) printf("`" #expr "` = " format "\n", (expr));

int strindex(const char *s, const char *t);

int main()
{
	dprint("%d", strindex("Lorem ipsum dolor sit amet, consectetur adipiscing elit", "it"));
	return 0;
}	

int strindex(const char *haystack, const char *needle)
{
	int i, j, k, rightmost = -1;
	
	for (i = 0; haystack[i]; ++i)
	{
		for (j = 0, k = i; needle[j] && haystack[k] == needle[j]; ++j, ++k)
			/* Do nothing */;

		if (j > 0 && needle[j] == '\0')
			rightmost = i;
	}
	return rightmost;
}
