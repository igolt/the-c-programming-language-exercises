#include "iolib.h"

#include <stdio.h>
#include <stdarg.h>

int eprint(const char *s)
{
  return fputs(s, stderr);
}

int eputs(const char *s)
{
  return fprintf(stderr, "%s\n", s);
}

int eprintf(const char *fmt, ...)
{
  va_list ap;
  int result;

  va_start(ap, fmt);
  result = vfprintf(stderr, fmt, ap);
  va_end(ap);

  return result;
}

#define BUFF_SIZE 100

static char buffer[BUFF_SIZE];
static char *bufp = buffer;

#define BUFF_END (buffer + BUFF_SIZE)

#define BUFF_IS_EMPTY (bufp == buffer)
#define BUFF_IS_FULL  (bufp == BUFF_END)

int getch(void)
{
	return (BUFF_IS_EMPTY) ? getchar() : (*--bufp);
}

int ungetch(int c)
{
	return (BUFF_IS_FULL || c == EOF)
		? EOF : (*bufp++ = c);
}
