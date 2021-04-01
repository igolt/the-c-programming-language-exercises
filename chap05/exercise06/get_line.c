#include <stdio.h>

#define MAXLINE 100

size_t getline(char *, size_t);

int main(void)
{
	char line[MAXLINE];
	size_t len = 0;

	while ((len=get_line(line, MAXLINE)) > 0)
		printf("%s", line);
	return 0;
}

size_t getline(char *line, size_t max)
{
	char *w, *end;

	if (max < 2)
		return 0;

	w = line;
	end = line + max - 1;
	while (w < end && (*w=getchar()) != EOF)
		if (*w++ == '\n')
			break;
	*w = '\0';
	return w - line;
}
