/*
 * Exercise 5-14. Modify the sort program to handle a -r flag,
 * which indicates sorting in reverse (decreasing) order. Be sure
 * that -r works with -n.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cbook/iolib.h>

#define bool signed char
#define true 1
#define false 0

#define MAXLINES 5000

#define ERR_INPUT_TOO_BIG 1

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *),
               bool reverse);

int numcmp(const char *, const char *);

int
main(int argc, char *argv[])
{
  const char *progname = *argv;
  int nlines;
  bool numeric = false;
  bool reverse = false;

  while (--argc > 0) {
    ++argv;

    if (strcmp(*argv, "-n") == 0)
      numeric = true;
    else if (strcmp(*argv, "-r") == 0)
      reverse = true;
  }

  if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
    eprintf("%s: input too big to sort\n", progname);
    return ERR_INPUT_TOO_BIG;
  }

  quicksort((void **) lineptr, 0, nlines - 1,
            (int (*)(void *, void *))((numeric) ? (numcmp) : (strcmp)),
            reverse);
  writelines(lineptr, nlines);
  return 0;
}

char *strdup(const char *);
void *alloc(size_t n);

int
readlines(char *lptr[], int maxlines)
{
  char line[1000];
  int nlines = 0;

  while (fgets(line, sizeof(line), stdin))
    if (nlines >= maxlines || (lptr[nlines++] = strdup(line)) == NULL)
      return -1;
  return nlines;
}

char *
strdup(const char *s)
{
  char *cpy;

  cpy = (char *) alloc(strlen(s) + 1);
  if (cpy == NULL)
    return NULL;
  return strcpy(cpy, s);
}

void
writelines(char *lineptr[], int nlines)
{
  while (nlines) {
    printf("%s", *lineptr++);
    --nlines;
  }
}

int
numcmp(const char *s1, const char *s2)
{
  double v1 = atof(s1);
  double v2 = atof(s2);

  if (v1 < v2)
    return -1;
  if (v1 == v2)
    return 0;
  return 1;
}

void
swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void
quicksort(void *v[], int left, int right, int (*comp)(void *, void *),
          bool reverse)
{
  int i, last;

  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; ++i) {
    int cmp_result = (*comp)(v[i], v[left]);

    if (reverse)
      cmp_result = -cmp_result;
    if (cmp_result < 0)
      swap(v, ++last, i);
  }
  swap(v, left, last);
  quicksort(v, left, last - 1, comp, reverse);
  quicksort(v, last + 1, right, comp, reverse);
}

#define MAX_ALLOC 500000

char _alloc[MAX_ALLOC];
char *allocp = _alloc;

#define ALLOC_END (_alloc + MAX_ALLOC)

void *
alloc(size_t n)
{
  if (allocp + n > ALLOC_END)
    return NULL;
  allocp += n;
  return (void *) (allocp - n);
}
