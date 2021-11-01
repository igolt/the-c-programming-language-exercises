/*
 * Exercise 5-6. Rewrite appropriate program from earlier chapters and
 * exercises with pointers instead of array indexing. good possibilities include
 * getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapter2, 3, and
 * 4) reverse (Chapter 3), and strindex and getop (Chapter 4).
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <cbook/strlib.h>

static int ATOI(const char *s);
static void test_atoi(void);

static int getline(char *, int);
static void test_getline(void);

static char *itoa(int val, char *s);
static void test_itoa(void);

static int strindex(const char *haystack, const char *needle);
static void test_strindex(void);

int
main(void)
{
  test_atoi();
  test_itoa();
  test_getline();
  test_strindex();
  return 0;
}

static void
test_atoi(void)
{
  assert(5 == ATOI("   5"));
  assert(5 == ATOI("+5"));
  assert(-892 == ATOI("  -892"));
  assert(0 == ATOI("   - 892"));
  assert(298 == ATOI("   +298 765"));
  assert(298 != ATOI("765"));

  printf("Sucess!!!\n");
}

static int
ATOI(const char *s)
{
  int val;
  char sig;

  while (isspace(*s))
    ++s;

  sig = (*s == '-') ? '-' : '+';

  if (*s == '+' || *s == '-')
    ++s;

  val = 0;
  while (isdigit(*s))
    val = val * 10 + *s++ - '0';
  return (sig == '-') ? -val : val;
}

static void
test_getline(void)
{
  char line[1000];

  while (getline(line, sizeof(line)) > 0)
    printf("%s", line);
}

static int
getline(char *line, int size)
{
  char *w = line;
  int c;

  while (--size && (c = getchar()) != EOF) {
    if ((*w++ = c) == '\n')
      break;
  }
  *w = '\0';
  return w - line;
}

static void
test_itoa(void)
{
  char result[100];

  assert(strcmp("2489", itoa(2489, result)) == 0);
  assert(strcmp("0", itoa(0, result)) == 0);
  assert(strcmp("9", itoa(9, result)) == 0);
  assert(strcmp("-234", itoa(-234, result)) == 0);

  printf("De boas B-)!\n");
}

static char *
itoa(int val, char *s)
{
  char *it;
  int is_negative = (val < 0);

  it = s;
  do {
    *it++ = abs(val % 10) + '0';
  } while ((val /= 10));

  if (is_negative)
    *it++ = '-';
  *it = '\0';
  return strreverse(s);
}

static void
test_strindex(void)
{
  assert(strindex("Lorem ipsum dolor sit amet", "iaculis") == -1);
  assert(strindex("Lorem ipsum", "") == -1);
}

static int
strindex(const char *haystack, const char *needle)
{
  if (*needle) {
    const char *it;

    for (it = haystack; *it; ++it) {
      const char *hay = it;
      const char *nee = needle;

      while (*nee && *hay == *nee)
        ++nee, ++hay;

      if (*nee == '\0')
        return it - haystack;
    }
  }
  return -1;
}
