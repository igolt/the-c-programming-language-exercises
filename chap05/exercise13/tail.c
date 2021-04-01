/*
 * Exercise 5-13. Write the program tail, which prints
 * the last n lines of its input. By default n is set to 10,
 * let us say, but it can be changed by an option argument so that
 *   tail -n
 * prints the last n lines. The program should behave rationally no
 * matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of avaiable storage;
 * lines should be stored as in the sorting program of Section 5.6,
 * not in a two-dimensional array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define bool signed char
#define true  1
#define false 0

#define MAX_LINE 1000

#define DEFAULT_N_LINES 10

#define ERR_INVAL_USAGE 1
#define ERR_INVAL_ARG   2
#define ERR_ALLOC       3

#define TAIL_INIT() \
	tail = malloc(sizeof(*tail) * nlines), pos = 0;

#define TAIL_PUSH(__line)                                    \
	do                                                       \
	{                                                        \
		if (pos == nlines)                                   \
		{                                                    \
			pos = 0;                                         \
			rewrite = true;                                  \
		}                                                    \
		if (rewrite)                                         \
		{                                                    \
			size_t linelen = strlen(__line);                 \
                                                             \
			if (linelen > strlen(tail[pos]))                 \
				tail[pos] = realloc(tail[pos], linelen + 1); \
			strcpy(tail[pos], __line);                       \
		}                                                    \
		else                                                 \
			tail[pos] = strdup(__line);                      \
		++pos;                                               \
	} while (0)

#define TAIL_PRINT_N_FREE()                       \
	do                                            \
	{                                             \
		long int count;                           \
		                                          \
		if (rewrite)                              \
		{                                         \
			count = pos;                          \
                                                  \
			do                                    \
			{                                     \
				printf("%s", tail[count]);        \
				free(tail[count]);                \
				count = (count + 1) % nlines;     \
			} while (count != pos);               \
		}                                         \
		else                                      \
		{                                         \
			for (count = 0; count < pos; ++count) \
			{                                     \
				printf("%s", tail[count]);        \
				free(tail[count]);                \
			}                                     \
		}                                         \
                                                  \
		free(tail);                               \
	} while (0)

const char *progname;
long int nlines;

void process_args(int argc, char *argv[]);
char *strdup(const char *s);

int main(int argc, char *argv[])
{
	char line[MAX_LINE];
	char **tail;
	bool rewrite = false;
	long int pos;

	process_args(argc, argv);

	if (nlines == 0)
		return 0;

	TAIL_INIT();

	while (fgets(line, MAX_LINE, stdin))
		TAIL_PUSH(line);

	TAIL_PRINT_N_FREE();
	return 0;
}

char *strdup(const char *s)
{
	char *cpy;

	cpy = (char *) malloc(strlen(s) + 1);
	if (cpy == NULL)
		return NULL;
	return strcpy(cpy, s);
}

void process_args(int argc, char *argv[])
{
	extern long int nlines;
	extern const char *progname;

	assert(argc > 0);
	assert(argv != NULL);

	progname = *argv;

	if (argc < 2)
		nlines = DEFAULT_N_LINES;
	else
	{
		while (--argc > 0)
		{
			const char *arg = *++argv;

			if (*arg != '-')
			{
				fprintf(stderr, "Usage: %s [-NLINES]\n", progname);
				exit(ERR_INVAL_USAGE);
			}
			else
			{
				char *saveptr;

				nlines = strtol(++arg, &saveptr, 10);

				if (*saveptr || nlines < 0)
				{
					fprintf(stderr, "%s: invalid argument `%s`\n", progname, arg);
					exit(ERR_INVAL_ARG);
				}
			}
		}
	}
}
