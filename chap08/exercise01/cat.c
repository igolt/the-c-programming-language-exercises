/*
 * Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open,
 * and close instead of their standard library equivalents. Perform experiments
 * to determine the relative speeds of the two versions.
 */

/* Note: I'm using Linux */
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>

#include <cbook/iolib.h>
#include <cbook/strlib.h>

#define PROGNAME "cat"

#define BUFFERSIZE 4096

#define STDIN_FD 0
#define STDOUT_FD 1

#define streq(s1, s2) (strcmp((s1), (s2)) == 0)

static void
report(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  fputs(PROGNAME ": ", stderr);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
}

static void
fcopy(int src_fd, const char *fname)
{
  char buffer[BUFFERSIZE];
  int n_read;

  while ((n_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
    if (n_read != write(STDOUT_FD, buffer, n_read)) {
      report("failed copying from `%s`: write error", fname);
      return;
    }
  }

  if (n_read != 0) {
    report("failed copying from `%s`: read error", fname);
  }
}

int
main(int argc, const char *argv[])
{
  if (argc == 1)
    fcopy(STDIN_FD, "stdin");
  else {
    while (--argc) {
      if (streq(*++argv, "-")) {
        fcopy(STDIN_FD, "stdin");
      } else {
        int src_fd;

        src_fd = open(*argv, O_RDONLY, 0);

        if (src_fd == -1) {
          report("failed opening file `%s`\n", *argv);
        } else {
          fcopy(src_fd, *argv);
        }
      }
    }
  }
  return 0;
}
