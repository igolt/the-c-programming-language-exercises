/*
 * Exercise 6-3. Write a cross-referencer that prints a list of all words in a
 * document, and for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so on.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <cbook/iolib.h>
#include <cbook/utils.h>
#include <cbook/strlib.h>
#include <cbook/boolean.h>

#define stringcmp strcasecmp

enum { WORD, NEW_LINE };

struct llistnode {
  struct llistnode *next;
  size_t linenr;
};

struct llist {
  struct llistnode *first;
  struct llistnode *last;
};

struct tnode {
  struct llist lines;
  char *word;
  struct tnode *left;
  struct tnode *right;
};

static struct llistnode *
llistnode_new(size_t linenr)
{
  struct llistnode *node = malloc(sizeof(*node));

  if (node) {
    node->linenr = linenr;
    node->next   = NULL;
  }
  return node;
}

static void
llist_init(struct llist *self)
{
  self->first = self->last = NULL;
}

static void
llist_push(struct llist *self, size_t linenr)
{
  if (self->first == NULL) {
    self->first = self->last = llistnode_new(linenr);
  } else if (self->last->linenr != linenr) {
    struct llistnode *node = llistnode_new(linenr);

    self->last->next = node;
    self->last       = node;
  }
}

static struct tnode *
tnode_new(const char *word, size_t linenr)
{
  struct tnode *node = malloc(sizeof(*node));

  if (node) {
    node->word = strdup(word);
    node->left = node->right = NULL;
    llist_init(&node->lines);
    llist_push(&node->lines, linenr);
  }
  return node;
}

static bool
isnoiseword(const char *word)
{
  static const char *const noisewords[] = {
    "a",  "an", "and",  "are", "in",   "is",
    "of", "or", "that", "the", "this", "to",
  };
  const char *const *low  = noisewords;
  const char *const *high = noisewords + ARRAYSIZE(noisewords);

  while (low < high) {
    const char *const *mid = low + (high - low) / 2;
    int cond               = stringcmp(word, *mid);

    if (cond == 0) {
      return true;
    } else if (cond < 0) {
      high = mid;
    } else
      low = mid + 1;
  }
  return false;
}

static struct tnode *
addtree(struct tnode *root, const char *word, size_t linenr)
{
  if (!isnoiseword(word)) {
    if (root == NULL) {
      root = tnode_new(word, linenr);
    } else {
      struct tnode *parent = root;

      while (1) {
        struct tnode **child;
        int cmp = stringcmp(word, parent->word);

        if (cmp == 0) {
          llist_push(&parent->lines, linenr);
          break;
        }

        child = (cmp < 0) ? &parent->left : &parent->right;

        if (*child == NULL) {
          *child = tnode_new(word, linenr);
          break;
        }
        parent = *child;
      }
    }
  }
  return root;
}

int
_getword(char *word, int n)
{
  char *w = word;
  int c, type;

  while (isspace(c = getch())) {
    if (c == '\n') {
      strcpy(word, "\n");
      return NEW_LINE;
    }
  }

  if (c == EOF)
    return EOF;

  *w++ = c;

  if (isalpha(c)) {
    type = WORD;
    while (--n > 1 && isalpha(c = getch()))
      *w++ = c;
    ungetch(c);
  } else {
    type = c;
  }
  *w = '\0';
  return type;
}

void
tree_print(const struct tnode *node)
{
  if (node) {
    const struct llistnode *it;

    tree_print(node->left);

    printf("%s: ", node->word);

    for (it = node->lines.first;;) {
      printf("%lu", it->linenr);

      if ((it = it->next) == NULL)
        break;
      printf(", ");
    }
    putchar('\n');

    tree_print(node->right);
  }
}

int
main(void)
{
  char word[200];
  struct tnode *root;
  size_t linenr;
  int type;

  linenr = 1;
  root   = NULL;
  while ((type = _getword(word, sizeof(word))) != EOF) {
    if (type == WORD)
      root = addtree(root, word, linenr);
    else if (type == NEW_LINE)
      ++linenr;
  }

  tree_print(root);
  return 0;
}
