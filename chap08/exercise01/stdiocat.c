/*
 * Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open,
 * and close instead of their standard library equivalents. Perform experiments
 * to determine the relative speeds of the two versions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <cbook/iolib.h>

static void
error(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}

#define COPY_TO_STDOUT(infile)                                                 \
  do {                                                                         \
    while (fgets(buf, BUFSIZ, (infile)))                                       \
      if (print(buf) == EOF)                                                   \
        error("%s: write error\n");                                            \
  } while (0)

int
main(int argc, const char *const argv[])
{
  const char *const progname = *argv;
  char buf[BUFSIZ];

  if (argc == 1)
    COPY_TO_STDOUT(stdin);
  else {
    while (--argc) {
      FILE *fp;

      if ((fp = fopen(*++argv, "r")) == NULL) {
        eprintf("%s: could not open file `%s`\n", progname, *argv);
        continue;
      }
      COPY_TO_STDOUT(fp);
      fclose(fp);
    }
  }
  return 0;
}
