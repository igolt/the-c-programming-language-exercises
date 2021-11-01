/*
 * Exercise 4-9. Our getch and ungetch do not handle a push-back EOF
 * correctly. Decide what their propertier ought to be if an EOF is
 * pushed back, then implement your design.
 */

#include <assert.h>
#include <stdio.h>

#define SUCESS       0
#define ERR_BUF_FULL 1
#define ERR_EOF_PUSH 2

int ungetch(int);
int getch(void);
void fill_buf(void);

int
main(void)
{
  assert(SUCESS == ungetch('a'));
  assert(ERR_EOF_PUSH == ungetch(EOF));
  assert('a' == getch());

  fill_buf();

  assert(ERR_BUF_FULL == ungetch('a'));

  return 0;
}

#define BUFSIZE 100

char buf[BUFSIZE];
size_t bufp = 0;

#define BUF_FULL  (bufp == BUFSIZE)
#define BUF_EMPTY (bufp == 0)

int
ungetch(int c)
{
  if (c == EOF)
    return ERR_EOF_PUSH;
  if (BUF_FULL)
    return ERR_BUF_FULL;
  buf[bufp++] = c;
  return SUCESS;
}

int
getch(void)
{
  return (BUF_EMPTY) ? getchar() : buf[--bufp];
}

void
fill_buf(void)
{
  while (!BUF_FULL)
    ungetch('0');
}
