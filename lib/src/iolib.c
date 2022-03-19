#include "iolib.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#define FGETCH(stream)     ((stream) == stdin ? getch()    : getc(stream))
#define UNGETCH(c, stream) ((stream) == stdin ? ungetch(c) : ungetc(c, stream))

int
fgetline(char *line, int max, FILE *stream)
{
  int c;
  int i;

  --max;
  i = 0;

  while (i < max && (c = FGETCH(stream)) != EOF)
    if ((line[i++] = c) == '\n')
      break;
  line[i] = '\0';

  return i;
}

char *
fgetword(char *word, int size, FILE *stream)
{
  int c;
  char *w = word;

  if (size < 2)
    return NULL;

  while (isspace(c = FGETCH(stream)))
    continue;

  if (c == EOF)
    return NULL;

  *w++ = c;

  if (isalnum(c) || c == '_') {
    while (--size > 1 && (isalnum(c = FGETCH(stream)) || c == '_'))
      *w++ = c;

    if (size > 1 && c != EOF)
      UNGETCH(c, stream);
  }
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
