#include "iolib.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

int
fgetline(char *line, int max, FILE *stream)
{
  int c;
  int i;

  --max;
  i = 0;

  while (i < max && (c = fgetc(stream)) != EOF)
    if ((line[i++] = c) == '\n')
      break;
  line[i] = '\0';

  return i;
}

static int
iswordchar(int c)
{
  return c == '_' || isalnum(c);
}

char *
fgetword(char *word, int size, FILE *stream)
{
  int c;
  char *w = word;

  if (size < 2)
    return NULL;

  while (isspace(c = getc(stream)))
    /* Skip white spaces */;

  if (c == EOF)
    return NULL;

  --size;
  do
    *w++ = c;
  while (--size && iswordchar(c = getc(stream)));
  *w = '\0';

  if (size && c != EOF)
    ungetc(c, stream);
  return word;
}

int
eprintf(const char *fmt, ...)
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

#define BUFF_IS_EMPTY() (bufp == buffer)
#define BUFF_IS_FULL()  (bufp == BUFF_END)

int
getch(void)
{
  return (BUFF_IS_EMPTY()) ? getchar() : (*--bufp);
}

int
ungetch(int c)
{
  return (BUFF_IS_FULL() || c == EOF) ? EOF : (*bufp++ = c);
}
