/*
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 */
#include <ctype.h>
#include <stdio.h>

#include <cbook/utils.h>

int
main(void)
{
  unsigned tabs, nl, blanks;
  int c;

  tabs = nl = blanks = 0;
  while ((c = getchar()) != EOF) {
    if (isblank(c)) {
      ++blanks;
      if (c == '\t')
        ++tabs;
    } else if (c == '\n')
      ++nl;
  }
  printf("Tabs: %u\n", tabs);
  printf("New lines: %u\n", nl);
  printf("Blanks: %u\n", blanks);
  return 0;
}
