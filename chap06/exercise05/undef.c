/*
 * Exercise 6-5. Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install.
 */
#include <stdlib.h>
#include <string.h>

#include <cbook/alloc.h>
#include <cbook/iolib.h>
#include <cbook/utils.h>
#include <cbook/strlib.h>

#define stringcmp strcmp

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
nlist_search(struct nlist *node, const char *s)
{
  for (; node; node = node->next)
    if (stringcmp(s, node->name) == 0)
      return node;
  return NULL;
}

#define lookup(name) nlist_search(hashtab[hash(name)], name)

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

    np->next         = hashtab[hashval];
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
  np   = *head;
  while (np) {
    if (stringcmp(np->name, name) == 0) {
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
    np   = np->next;
  }
  return NOT_FOUND;
}

/* getline but removes '\n' */
static int
read_line(char *s, int size)
{
  int len;

  if ((len = getline(s, size)) > 0)
    if (s[len - 1] == '\n')
      s[len - 1] = '\0';
  return len;
}

static void
menu_install(void)
{
  char name[100];
  char defn[200];

  printf("Name: ");
  read_line(name, sizeof(name));
  printf("Replacement: ");
  read_line(defn, sizeof(defn));

  if (install(name, defn) == NULL)
    printf("error: could not install: (`%s`, `%s`)\n", name, defn);
}

static void
menu_undef(void)
{
  char name[100];

  printf("Name: ");
  read_line(name, sizeof(name));

  if (undef(name) != REMOVED)
    printf("error: could not remove `%s`\n", name);
}

static void
menu_lookup(void)
{
  struct nlist *np;
  char name[100];

  printf("Name: ");
  read_line(name, sizeof(name));

  if ((np = lookup(name)))
    printf("#define %s %s\n", np->name, np->defn);
  else
    printf("error: `%s` not found\n", name);
}

static void
all_definitions(void)
{
  struct nlist *it;
  size_t i;

  for (i = 0; i < HASHSIZE; ++i)
    for (it = hashtab[i]; it; it = it->next)
      printf("#define %s %s\n", it->name, it->defn);
}

static void
clear_input(void)
{
  int c;

  while ((c = getchar()) != '\n' && c != EOF)
    continue;
}

int
main(void)
{
  struct {
    const char *title;
    void (*action)(void);
  } menuoptions[] = {
    { "Install"        , menu_install    },
    { "Undef"          , menu_undef      },
    { "Lookup"         , menu_lookup     },
    { "All definitions", all_definitions },
  };
  size_t i;

#define EXIT 0lu

#define IS_VALID_OPTION(opt) ((opt) <= ARRAYSIZE(menuoptions))

  while (1) {
    for (i = 0; i < ARRAYSIZE(menuoptions); ++i)
      printf("%lu - %s\n", i + 1, menuoptions[i].title);
    printf("%lu - Exit\n", EXIT);
    printf("R: ");

    if (scanf("%lu", &i) == 1) {
      if (IS_VALID_OPTION(i)) {
        if (i == EXIT)
          break;
        clear_input();
        (*menuoptions[i - 1].action)();
      } else
        printf("*** Invalid option ***\n");
    } else if (feof(stdin) || ferror(stdin))
      break;
    else {
      clear_input();
      printf("*** Invalid input ***\n");
    }

    putchar('\n');
  }
  return 0;
}
