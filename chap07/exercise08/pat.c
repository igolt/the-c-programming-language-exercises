/*
 * Exercise 7-8. Write a program to print a set of files, starting each new one
 * on a new page, with a title and a running page count for each file.
 */
#include <stdio.h>

#include <cbook/iolib.h>
#include <cbook/boolean.h>

#define ERR_INVAL_ARGC 1

int
main(int argc, const char *const argv[])
{
  const char *const progname = *argv;
  bool notfirstfile = false;

  if (argc == 1) {
    eprintf("Usage: %s FILE...\n", progname);
    return ERR_INVAL_ARGC;
  }

  while (--argc) {
    FILE *fp;

    if ((fp = fopen(*++argv, "r")) == NULL) {
      eprintf("%s: `%s`: ", progname, *argv);
      perror("");
    } else {
      char line[100];
      size_t linenr;

      if (notfirstfile)
        putchar('\n');
      printf("%s\n", *argv);

      linenr = 0;
      while (fgets(line, sizeof(line), fp))
        printf("%3lu: %s", ++linenr, line);
      notfirstfile = true;
    }
  }
  return 0;
}
