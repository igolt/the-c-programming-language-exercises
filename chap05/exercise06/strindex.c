#include <stdio.h>

#include "test.h"

int strindex(const char *, const char *);

int main(void)
{
	test(strindex("Lorem ipsum dolor sit amet", "iaculis") == -1);
	test(strindex("Lorem ipsum", "") == -1);
	return 0;
}

int strindex(const char *haystack, const char *needle)
{
	if (*needle)
	{
		char *it;

		for (it = haystack; *it; ++it)
		{
			char *hay = it;
			char *nee = needle;
	
			while (*nee && *hay == *nee)
				++nee, ++hay;
	
			if (*nee == '\0')
				return it - haystack;
		}
	}
	return -1;
}
