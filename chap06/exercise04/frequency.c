/*
 * Exercise 6-4. Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word
 * by its count.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cbook/iolib.h>
#include <cbook/strlib.h>
#include <cbook/quicksort.h>

enum { WORD, NEW_LINE };

struct key {
  char *word;
  unsigned count;
};

struct tnode {
  struct key info;
  struct tnode *left;
  struct tnode *right;
};

struct tree {
  struct tnode *root;
  size_t size;
};

#define tree_new() { NULL, 0 }

static struct tnode *
tnode_new(const char *word)
{
  struct tnode *node = malloc(sizeof(*node));

  if (node) {
    node->info.word  = strdup(word);
    node->info.count = 1;

    node->left = node->right = NULL;
  }
  return node;
}

static void
addtree(struct tree *self, const char *word)
{
  if (self->root == NULL) {
    self->root = tnode_new(word);
  } else {
    struct tnode *parent = self->root;

    while (1) {
      struct tnode **child;
      int cmp = strcmp(word, parent->info.word);

      if (cmp == 0) {
        ++parent->info.count;
        break;
      }

      child = (cmp < 0) ? &parent->left : &parent->right;

      if (*child == NULL) {
        *child = tnode_new(word);
        ++self->size;
        break;
      }
      parent = *child;
    }
  }
}

struct nodelist {
  struct tnode **array;
  size_t size;
};

static void
nodelist_init(struct nodelist *self, size_t capacity)
{
  self->array = malloc(sizeof(struct tnode *) * capacity);
  self->size  = 0;
}

#define nodelist_free(self) (free((self)->array))

static int
nodecmp(const void *n1, const void *n2)
{
  unsigned count1 = (*((struct tnode **) n1))->info.count;
  unsigned count2 = (*((struct tnode **) n2))->info.count;

  return (count1 > count2) ? -1 : (count1 == count2) ? 0 : 1;
}

static void
nodelist_sort(struct nodelist *self)
{
  quicksort(self->array, self->size, sizeof(struct tnode *), nodecmp);
}

static void
addlist(struct nodelist *self, struct tnode *node)
{
  if (node) {
    addlist(self, node->left);
    self->array[self->size++] = node;
    addlist(self, node->right);
  }
}

static void
treeprint(const struct tree *t)
{
  struct nodelist list;
  size_t i;

  nodelist_init(&list, t->size);
  addlist(&list, t->root);
  nodelist_sort(&list);

  for (i = 0; i < list.size; ++i) {
    struct key info = list.array[i]->info;

    printf("%u: %s\n", info.count, info.word);
  }
  nodelist_free(&list);
}

static int
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

int
main(void)
{
  char word[200];
  struct tree tree = tree_new();
  int type;

  while ((type = _getword(word, sizeof(word))) != EOF)
    if (type == WORD)
      addtree(&tree, word);

  treeprint(&tree);
  return 0;
}
