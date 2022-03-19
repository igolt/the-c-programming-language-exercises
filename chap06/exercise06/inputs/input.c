  
/*
 * Exercise 6-6. Implement a simple version of the #define
 * processor (i.e, no arguments) suitable for use with C
 * programs, based on the routines of this section. You may
 * also find getch and ungetch helpful.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cbook/utils.h>
#include <cbook/alloc.h>
#include <cbook/iolib.h>
#include <cbook/strlib.h>

#define HASHSIZE 101

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

static unsigned
hash(const char *s)
{
  unsigned hashval;

  for (hashval = 0; *s; ++s)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

static struct nlist *
nlist_search(struct nlist *node, const char *name)
{
  for (; node; node = node->next)
    if (strcmp(name, node->name) == 0)
      return node;
  return NULL;
}

/* #define lookup(name) nlist_search(hashtab[hash(name)], name) */

static struct nlist *
install(const char *name, const char *defn)
{
  struct nlist *np;
  unsigned hashval;

  hashval = hash(name);

  if ((np = nlist_search(hashtab[hashval], name)))
    memfree(np->defn);
  else {
    np = (struct nlist *) alloc(sizeof(*np));

    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;

    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  return ((np->defn = strdup(defn)) == NULL) ? NULL : np;
}

enum { REMOVED, NOT_FOUND };

static int
undef(const char *name)
{
  struct nlist *prev, *np, **head;

  prev = NULL;
  head = &hashtab[hash(name)];
  np = *head;
  while (np) {
    if (strcmp(np->name, name) == 0) {
      if (prev)
        prev->next = np->next;
      else
        *head = NULL;

      memfree(np->name);
      memfree(np->defn);
      memfree(np);

      return REMOVED;
    }

    prev = np;
    np = np->next;
  }
  return NOT_FOUND;
}

static int
_getline(char *line, int max)
{
  int c, i;

  if (--max < 1)
    return 0;

  for (i = 0; i < max && (c = getch()) != EOF; ++i)
    if ((line[i] = c) == '\n')
      break;
  line[i] = '\0';
  return i;
}

static int
_getword(char *word, int capacity)
{
  int c;
  char *w = word;

  if (--capacity < 1 || (c = getch()) == EOF)
    return EOF;

  *w++ = c;

  if (isspace(c)) {
    for (; --capacity; *w++ = c) {
      if (!isspace(c = getch())) {
        ungetch(c);
        break;
      }
    }
  } else if (c == '_' || c == '#' || isalpha(c)) {
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
        if (--capacity == 0 || (c = getch()) == EOF) {
          break;
        }
        *w++ = c;
      }
    }
  } else if (c == '/') {
    if (--capacity && (c = getch()) == '*') {
      *w++ = c;
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

int
main(void)
{
  char buff[300];
  struct nlist *np;
  int c;

  while (_getword(buff, sizeof(buff)) != EOF) {
    if ((np = lookup(buff))) {
      eprintf("Replacing `%s` with `%s`\n", buff, np->defn);
      print(np->defn);
    } else {
      if (strcmp("#define", buff) == 0) {
        char defn[200];

        while (isblank(c = getch()))
          continue;
        ungetch(c);

        if (_getword(buff, sizeof(buff)) == EOF)
          break;

        while (isblank(c = getch()))
          continue;
        ungetch(c);

        if (_getline(defn, sizeof(defn)) == 0)
          break;

        eprintf("install(`%s`, `%s`)\n", buff, defn);
        install(buff, defn);
      } else if (strcmp("#undef", buff) == 0) {
        if (_getword(buff, sizeof(buff)) == EOF)
          break;

        undef(buff);
      } else {
        print(buff);
      }
    }
  }
  return 0;
}
