/*
 * Exercise 5-11. Modify the program entab and
 * detab (written as exercises in Chapter 1)
 * to accept a list of tabstops as arguments.
 * Use the default tab settings if there are no arguments
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TABSTOP 8

#define ERR_INVAL_ARGC 1
#define ERR_NOT_A_VALID_NUM 2

int
main(int argc, char *argv[])
{
	const char *progname = *argv;
	unsigned tabstop;
	unsigned linelen;
	unsigned aux;
	int c;

	if (argc < 2) {
		tabstop = DEFAULT_TABSTOP;
	} else if (argc != 2) {
		fprintf(stderr, "%s: Usage [TABSTOP]\n", progname);
		return ERR_INVAL_ARGC;
	} else if ((tabstop=atoi(*++argv)) <= 0) {
		fprintf(stderr, "%s: invalid argument `%s'\n", progname, *argv);
		return ERR_NOT_A_VALID_NUM;
	}

	linelen = 0;
	while ((c=getchar()) != EOF) {
		if (c == '\t') {
			aux = tabstop - (linelen % tabstop);
			linelen += aux;

			while (aux) {
				putchar(' ');
				--aux;
			}
			continue;
		}
		putchar(c);
		if (c == '\n')
			linelen = 0;
		else
			++linelen;
	}
	return 0;
}
