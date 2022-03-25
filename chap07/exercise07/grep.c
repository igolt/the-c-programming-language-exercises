/*
 * Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its
 * input from a set of named files or, if no files are named as arguments, from
 * the standard input. Should the file name be printed when a matching line is
 * found?
 */
#include <stdio.h>
#include <string.h>

#include <cbook/iolib.h>

#define ERR_INVAL_ARGC 1

static char *
read_line(char *line, int maxline, FILE *stream)
{
  if ((line = fgets(line, maxline, stream))) {
    size_t len = strlen(line);

    if (len && line[len - 1] == '\n')
      line[len - 1] = '\0';
  }
  return line;
}

#define COPY_TO_STDOUT(infile)                                                 \
  do {                                                                         \
    while (read_line(line, sizeof(line), (infile)))                            \
      if (strstr(line, pattern))                                               \
        printf("%s:%s\n", *argv, line);                                        \
  } while (0)

int
main(int argc, const char *const argv[])
{
  char line[300];
  const char *const progname = *argv;
  const char *pattern;

  if (--argc == 0) {
    eprintf("Usage: %s PATTERN [FILE...]\n", progname);
    return ERR_INVAL_ARGC;
  }

  pattern = *++argv;

  if (argc == 1)
    COPY_TO_STDOUT(stdin);
  else {
    while (--argc) {
      FILE *fp;

      if ((fp = fopen(*++argv, "r")) == NULL) {
        eprintf("%s: `%s`: ", progname, *argv);
        perror("");
        continue;
      }

      COPY_TO_STDOUT(fp);
      fclose(fp);
    }
  }
  return 0;
}
