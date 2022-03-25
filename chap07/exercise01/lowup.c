/*
 * Exercise 7-1. Write a program that converts upper case to lower or lower
 * case to upper, depending on the name it is invoked with, as found in
 * argv[0].
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define UNUSED(var) ((void) var)

int
main(int argc, const char *const argv[])
{
  const char *progname;
  int (*convert)(int);
  int c;

  UNUSED(argc);

  progname = (strncmp("./", *argv, 2) == 0) ? *argv + 2 : *argv;
  convert  = (strcmp("upper", progname)) ? tolower : toupper;

  while ((c = getchar()) != EOF)
    putchar(convert(c));
  return 0;
}
