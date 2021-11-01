#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DO_NOTHING /**/
#define NOT_FOUND  (-1)

#define MAXWORD 100

struct key {
  const char *word;
  unsigned count;
} keytab[] = {
  {"auto"    , 0},
  {"break"   , 0},
  {"case"    , 0},
  {"char"    , 0},
  {"const"   , 0},
  {"continue", 0},
  {"default" , 0},
  {"unsigned", 0},
  {"void"    , 0},
  {"volatile", 0},
  {"while"   , 0},
  {"while"   , 0},
};

#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

int getword(char *, int);
int binsearch(const char *, struct key[], int);

int
main(void)
{
  int n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]))
      if ((n = binsearch(word, keytab, NKEYS)) >= 0)
        ++keytab[n].count;
  }

  for (n = 0; n < NKEYS; ++n)
    if (keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count, keytab[n].word);

  return 0;
}

int
getword(char *word, int max)
{
  int c;

  if (max <= 0)
    return EOF;

  while (isspace(c = getchar()))
    DO_NOTHING;

  if (c != EOF)
    *word++ = c;

  if (!isalpha(c)) {
    *word = '\0';
    return c;
  }

  for (; --max > 0; ++word) {
    if (!isalnum(*word = getchar())) {
      /* ungetch(*w); */
      break;
    }
  }
  *word = '\0';
  return c;
}

int
binsearch(const char *word, struct key keytab[], int size)
{
  int low, high, mid;

  low = 0;
  high = size - 1;

  while (low <= high) {
    int comp;

    mid = (low + high) / 2;

    if ((comp = strcmp(keytab[mid].word, word)) == 0)
      return mid;
    else if (comp > 0)
      low = mid;
    else
      high = mid;
  }
  return NOT_FOUND;
}
