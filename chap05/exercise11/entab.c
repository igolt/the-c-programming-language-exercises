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
	unsigned nb;
	unsigned nt;
	int c;

	if (argc < 2)
		tabstop = DEFAULT_TABSTOP;
	else if (argc != 2)
	{
		fprintf(stderr, "%s: Usage [TABSTOP]\n", progname);
		return ERR_INVAL_ARGC;
	}
	else if ((tabstop=atoi(*++argv)) <= 0)
	{
		fprintf(stderr, "%s: invalid argument `%s'\n", progname, *argv);
		return ERR_NOT_A_VALID_NUM;
	}

	linelen = nb = nt = 0;
	while ((c=getchar()) != EOF)
	{
		if (c == ' ')
		{
			++nb;
			++linelen;
			if (linelen % tabstop == 0)
			{
				nb = 0;
				putchar('\t');
			}
		}
		else
		{
			if (nb != 0)
			{
				linelen += nb;

				do
					putchar('*');
				while (--nb);
			}
			putchar(c);

			if (c == '\n')
				linelen = 0;
			else if (c == '\t')
				linelen += tabstop - (linelen % tabstop);
			else
				++linelen;
		}
	}
	return 0;
}
