/*
 * Exercise 1-5. Verify that the experssion getchar() != EOF is 0 or 1.
 */
#include <stdio.h>

int main()
{
	int c;

	do
		printf("getchar() != EOF is %d\n", (c=getchar()) != EOF);
	while (c != EOF);
	return 0;
}
