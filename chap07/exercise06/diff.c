/*
 * Exercise 7-6. Write a progam to compare two files, printing the first line
 * where they differ.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cbook/iolib.h>

#define STRNOTEQ(s1, s2) (strcmp((s1), (s2)))

enum { ERR_INVAL_ARGC = 1, ERR_FILE_FAIL };

#define FILE_OPEN(fp, filename)                                                \
  do {                                                                         \
    if (((fp) = fopen(filename, "r")) == NULL) {                               \
      eprintf("%s: `%s`: ", progname, filename);                               \
      perror("");                                                              \
      return ERR_FILE_FAIL;                                                    \
    }                                                                          \
  } while (0)

int
main(int argc, const char *const argv[])
{
  const char *const progname = *argv;
  FILE *fp1, *fp2;

  if (argc != 3) {
    eprintf("%s: expected 2 arguments, received %d\n", progname, argc - 1);
    return ERR_INVAL_ARGC;
  }

  FILE_OPEN(fp1, argv[1]);
  FILE_OPEN(fp2, argv[2]);

  while (1) {
    char line1[1000], line2[1000];
    char *s1, *s2;

    s1 = fgets(line1, sizeof(line1), fp1);
    s2 = fgets(line2, sizeof(line2), fp2);

    if (s1 == NULL || s2 == NULL) {
      if (s1 || s2)
        puts((s1) ? s1 : s2);
      break;
    }

    if (STRNOTEQ(line1, line2)) {
      puts(line1);
      puts(line2);
      break;
    }
  }
  return 0;
}
