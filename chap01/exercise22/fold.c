/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 */
#include <stdio.h>

#include <cbook/utils.h>

#define FOLDCOLUMN 80
#define OFFSET     10

#define MAXBUFFER FOLDCOLUMN - 1

#define TABSTOP 8

#define TRUE  1
#define FALSE 0

int
main(void)
{
  char buffer[MAXBUFFER]; /* buffer to keep character after a occurrence of a
                             blank after a non-blank */
  int c;                  /* input character */
  int w;                  /* index to write on buffer */
  int i;                  /* index to iterate the buffer */
  int lastblank;          /* is there a blank after a non blank in this line ? TRUE :
                             FALSE */
  int inblank;            /* the last char was blank ? TRUE : FALSE */
  int linewidth;          /* linewidth :) */

  linewidth = w = 0;
  lastblank = FALSE;
  inblank = TRUE;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      if (lastblank) {
        for (i = 0; i < w; ++i)
          putchar(buffer[i]);
        w = 0;
        lastblank = FALSE;
      }
      linewidth = 0;
      inblank = TRUE;
    } else {
      if (c == '\t')
        linewidth += TABSTOP - (linewidth % TABSTOP);
      else
        ++linewidth;

      if (linewidth > FOLDCOLUMN && lastblank) {
        putchar('\n');
        for (i = 1; i < w; ++i)
          putchar(buffer[i]);
        linewidth = w;
        w = 0;
        lastblank = FALSE;
      } else if (linewidth > FOLDCOLUMN + OFFSET) {
        putchar('\n');
        if (c == '\t')
          linewidth = TABSTOP;
        else
          linewidth = 1;
        inblank = TRUE;
      }

      if (!isblank(c))
        inblank = FALSE;
      else if (!inblank) {
        if (lastblank) {
          for (i = 0; i < w; ++i)
            putchar(buffer[i]);
          w = 0;
        } else
          lastblank = TRUE;
        inblank = TRUE;
      }
    }
    if (lastblank)
      buffer[w++] = c;
    else
      putchar(c);
  }
  if (w != 0)
    for (i = 0; i < w; ++i)
      putchar(buffer[i]);
  return 0;
}
