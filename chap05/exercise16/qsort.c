/*
 * Exercise 5-16. Add the -d ("directory order") option, which
 * makes comparisons only on letters, numbers and blanks. Make
 * sure it works in conjunction with -f.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cbook/iolib.h>
#include <cbook/strlib.h>
#include <cbook/boolean.h>
#include <cbook/quicksort.h>

#define MAXLINES 5000

#define ERR_INPUT_TOO_BIG 1
#define ERR_INVAL_ARG     2

#define print_inval_opt(prefix, opt)                                           \
  eprintf("%s: invalid option -- '%c'\n", prefix, opt)

static bool reverse = false;

static int readlines(char *lineptr[], int nlines);
static void writelines(char *lineptr[], int nlines);

static int numcmp(const void *, const void *);
static int string_cmp(const void *, const void *);
static int directory_comp(const void *, const void *);
static int ignore_case_cmp(const void *, const void *);
static int directory_comp_ignore_case(const void *, const void *);

int
main(int argc, char *argv[])
{
  const char *progname = *argv;
  char *lineptr[MAXLINES];
  compfunc_t comp;
  int nlines;
  bool ignore_case;
  extern bool reverse;

  comp        = string_cmp;
  ignore_case = false;

  while (--argc > 0) {
    char *current_arg = *++argv;

    if (current_arg[0] != '-' || current_arg[1] == '\0') {
      print_inval_opt(progname, *current_arg);
      return ERR_INVAL_ARG;
    }

    while (*++current_arg != '\0') {
      switch (*current_arg) {
        case 'n':
          comp = numcmp;
          break;

        case 'r':
          reverse = true;
          break;

        case 'f':
          if (comp == string_cmp)
            comp = ignore_case_cmp;
          else if (comp == directory_comp)
            comp = directory_comp_ignore_case;
          ignore_case = true;
          break;

        case 'd':
          comp = (ignore_case) ? directory_comp_ignore_case : directory_comp;
          break;

        default:
          print_inval_opt(progname, *current_arg);
          return ERR_INVAL_ARG;
      }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
    eprintf("%s: input too big to sort\n", progname);
    return ERR_INPUT_TOO_BIG;
  }

  quicksort((void *) lineptr, nlines, sizeof(*lineptr), comp);

  writelines(lineptr, nlines);
  return 0;
}

static int
readlines(char *lptr[], int maxlines)
{
  char line[1000];
  int nlines = 0;

  while (fgets(line, sizeof(line), stdin))
    if (nlines >= maxlines || (lptr[nlines++] = strdup(line)) == NULL)
      return -1;
  return nlines;
}

static void
writelines(char *lineptr[], int nlines)
{
  while (nlines) {
    printf("%s", *lineptr++);
    --nlines;
  }
}

static int
numcmp_base(double d1, double d2)
{
  if (d1 > d2)
    return 1;
  if (d1 == d2)
    return 0;
  return -1;
}

static int
numcmp(const void *p1, const void *p2)
{
  double d1 = atof(*(const char **) p1);
  double d2 = atof(*(const char **) p2);
  int result;
  extern bool reverse;

  result = numcmp_base(d1, d2);
  return reverse ? -result : result;
}

static int
string_cmp(const void *p1, const void *p2)
{
  const char *s1 = *(const char **) p1;
  const char *s2 = *(const char **) p2;
  int result;
  extern bool reverse;

  result = strcmp(s1, s2);
  return reverse ? -result : result;
}

static int
ignore_case_cmp(const void *p1, const void *p2)
{
  const char *s1 = *(const char **) p1;
  const char *s2 = *(const char **) p2;
  int result;
  extern bool reverse;

  result = strcasecmp(s1, s2);
  return reverse ? -result : result;
}

static int
directory_comp_base(const char *s1, const char *s2, bool fold)
{
  unsigned char c1;
  unsigned char c2;

#define SKIP_INVALID(s)                                                        \
  do {                                                                         \
    while (*s && !isalnum(*s) && !isspace(*s))                                 \
      ++s;                                                                     \
  } while (0)

  do {
    SKIP_INVALID(s1);
    SKIP_INVALID(s2);

    c1 = (fold) ? tolower(*s1++) : *s1++;
    c2 = (fold) ? tolower(*s2++) : *s2++;
  } while (c1 && c1 == c2);
  return c1 - c2;
}

static int
directory_comp_ignore_case(const void *p1, const void *p2)
{
  const char *s1 = *(const char **) p1;
  const char *s2 = *(const char **) p2;
  int result;
  extern bool reverse;

  result = directory_comp_base(s1, s2, true);

  return reverse ? -result : result;
}

static int
directory_comp(const void *p1, const void *p2)
{
  const char *s1 = *(const char **) p1;
  const char *s2 = *(const char **) p2;
  int result;
  extern bool reverse;

  result = directory_comp_base(s1, s2, false);

  return reverse ? -result : result;
}
