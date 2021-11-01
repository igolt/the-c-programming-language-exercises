/*
 * Exercise 2-2. Write a loop equivalent to the for loop above
 * without using && or ||.
 */
#include <stdio.h>

#define MAXLINE 100

#define TRUE  1
#define FALSE 0

int
get_line(char *line, int lim)
{
  int i = 0, c = EOF, isvalid = TRUE;

  /* for (i=0; i < lim - 1 && (c=getchar()) != '\n' && c != EOF; ++i) */
  --lim;
  while (isvalid) {
    if (i >= lim)
      isvalid = FALSE;
    else if ((c = getchar()) == EOF)
      isvalid = FALSE;
    else if (c == '\n')
      isvalid = FALSE;
    else
      line[i++] = c;
  }
  if (c == '\n')
    line[i++] = c;
  line[i] = '\0';
  return i;
}

int
main(void)
{
  char line[MAXLINE];

  while (get_line(line, MAXLINE) > 0)
    printf("%s", line);
  return 0;
}
