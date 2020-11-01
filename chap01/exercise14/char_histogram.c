/*
 * Exercise 1-14. Write a program to print a histogram of
 * the frequencies of different characters in its input.
 */
#include <stdio.h>
#include <ctype.h>

void print_histogram(const char *title, unsigned size)
{
	unsigned aux;

	printf("%10s: %4u ", title, size);
	for (aux = 0; aux < size; ++aux)
		putchar('|');
	putchar('\n');
}

int main()
{
	unsigned blanks;
	unsigned tabs;
	unsigned nls;
	unsigned alphas;
	unsigned digits;
	unsigned aux;
	int c;

	blanks = tabs = nls = alphas = digits = 0;
	while ((c=getchar()) != EOF)
	{
		if (isblank(c))
		{
			++blanks;
			if (c == '\t')
				++tabs;
		}
		else if (c == '\n')
			++nls;
		else if (isalpha(c))
			++alphas;
		else if (isdigit(c))
			++digits;
	}
	print_histogram("Blanks", blanks);
	print_histogram("Tabs", tabs);
	print_histogram("New lines", nls);
	print_histogram("Alphas", alphas);
	print_histogram("Digits", digits);
	return 0;
}
