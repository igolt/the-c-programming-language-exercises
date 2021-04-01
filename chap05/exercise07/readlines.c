#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXSTOR  10000

int readlines(char *[], int, char *, int);
void writelines(char *[], int);

int main(void)
{
	char *lineptr[MAXLINES];
	char alloc[MAXSTOR];
	int nlines;

	if ((nlines=readlines(lineptr, MAXLINES, alloc, MAXSTOR)) >= 0)
	{
		writelines(lineptr, nlines);
	}
	else
	{
		fputs("error: input too big to sort\n", stderr);
		return 1;
	}
	return 0;
}

int getline(char *, int);

#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines, char *storage, int freestorage)
{
	int nlines;
	int linelen;
	char line[MAXLEN];

	nlines = 0;
	while ((linelen=getline(line, MAXLEN)) > 0)
	{
		if (nlines >= maxlines || linelen > freestorage)
			return -1;

		line[linelen - 1] = '\0'; /* delete '\n' */
		strcpy(storage, line);
		lineptr[nlines++] = storage;

		/* update storage */
		storage += linelen;
		freestorage -=linelen;
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

int getline(char *line, int maxline)
{
	char *it;
	int c;

	it = line;
	while (--maxline > 0 && (c = getchar()) != EOF && (*it++ = c) != '\n')
		;
	return (it - line);
}

