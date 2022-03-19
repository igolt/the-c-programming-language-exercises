/*
 * Exercise 6-1. Our version of getword does not properly
 * handle underscores, string constants, comments, or
 * preprocessos control lines. Write a better version
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cbook/iolib.h>
#include <cbook/utils.h>

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
};

#define NKEYS ARRAYSIZE(keytab)

static struct key *binsearch(const char *, struct key[], size_t);
static int _getword(char *word, int capacity);

int
main(void)
{
  struct key *k;
  char word[MAXWORD];

  while (_getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      if ((k = binsearch(word, keytab, NKEYS)) != NULL)
        ++k->count;

  for (k = keytab; k < keytab + NKEYS; ++k)
    if (k->count > 0)
      printf("%4d %s\n", k->count, k->word);
}

static struct key *
binsearch(const char *word, struct key keytab[], size_t size)
{
  struct key *low, *mid, *high;

  low  = keytab;
  high = keytab + size;

  while (low < high) {
    int cmp;

    mid = low + (high - low) / 2;
    cmp = strcmp(word, mid->word);

    if (cmp == 0)
      return mid;
    else if (cmp < 0)
      high = mid;
    else
      low = mid + 1;
  }
  return NULL;
}

static int
_getword(char *word, int capacity)
{
  int c;
  char *w = word;

  if (--capacity < 1)
    return EOF;

  while (isspace(c = getch()))
    continue;

  if (c == EOF) {
    return EOF;
  }

  *w++ = c;

  if (c == '_' || c == '#' || isalpha(c)) {
    for (; --capacity; *w++ = c) {
      if (!isalnum(c = getch()) && c != '_') {
        ungetch(c);
        break;
      }
    }
  } else if (c == '"') {
    while (--capacity && (c = getch()) != EOF) {
      *w++ = c;

      if (c == '"') {
        break;
      } else if (c == '\\') {
        if (--capacity || (c = getch()) == EOF) {
          break;
        }
        *w++ = c;
      }
    }
  } else if (c == '/') {
    if (--capacity && (c = getch()) == '*') {
      while (--capacity && (c = getch()) != EOF) {
        *w++ = c;

        if (c == '*') {
          if (--capacity == 0 || (c = getch()) == EOF)
            break;
          *w++ = c;

          if (c == '/')
            break;
        }
      }
    } else {
      ungetch(c);
    }
  }

  *w = '\0';
  return word[0];
}
