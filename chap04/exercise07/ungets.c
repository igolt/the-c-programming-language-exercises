/*
 * Exercise 4-7. Write a routine ungets(s) that will push back
 * an entire string onto the input. Should ungets know about buf and
 * bufp, or should it just use ungetch?
 */

#include <stdio.h>

void ungets(const char *);
int ungetch(int);
int getch(void);

int
main(void)
{
  int c;

  ungets("\n)* rahc tsnoc(stegnu");
  while ((c = getch()) != EOF)
    putchar(c);
  return 0;
}

#define BUFSIZE 100

char buffer[BUFSIZE];
unsigned bufp = 0;

#define BUFF_IS_FULL  (bufp == BUFSIZE)
#define BUFF_IS_EMPTY (bufp == 0)

#define eputs(err_msg) (fputs(err_msg "\n", stderr))

void
ungets(const char *s)
{
  while (*s && ungetch(*s++) != EOF)
    continue;
}

int
ungetch(int c)
{
  if (BUFF_IS_FULL) {
    eputs("ungetch: error: buffer is full");
    return EOF;
  }
  if (c == EOF) {
    eputs("ungetch: error: cant push EOF");
    return EOF;
  }
  buffer[bufp++] = c;
  return 0;
}

int
getch(void)
{
  return (BUFF_IS_EMPTY) ? getchar() : buffer[--bufp];
}
