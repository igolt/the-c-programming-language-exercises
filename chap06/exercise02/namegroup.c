/*
 * Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the
 * first 6 characters, but different somewhere thereafter. Don't count words
 * within strings and comments. Make 6 a parameter that can be set from the
 * command line.
 */

#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <cbook/iolib.h>
#include <cbook/strlib.h>
#include <cbook/boolean.h>

struct tnode {
  char *word;
  struct tnode *left;
  struct tnode *right;
  unsigned gpnum;
};

struct cmpinfo {
  int comp;
  bool match;
};

static struct cmpinfo
stringcmp(const char *s1, const char *s2, int n)
{
  struct cmpinfo info;
  unsigned char c1, c2;

  while ((c1 = *s1) && c1 == (c2 = *s2))
    --n, ++s1, ++s2;

  info.match = n <= 0;
  info.comp  = c1 - c2;
  return info;
}

static struct tnode *
tnode_new(const char *word)
{
  struct tnode *node = malloc(sizeof(*node));

  if (node) {
    node->word  = strdup(word);
    node->gpnum = 0;
    node->left = node->right = NULL;
  }
  return node;
}

static struct tnode *
addtree(struct tnode *root, const char *word, const int num)
{
  static unsigned groupnumbercounter = 0;

  if (root == NULL) {
    root = tnode_new(word);
  } else {
    struct tnode *parent = root;
    int groupnumber      = 0;

    while (1) {
      struct tnode **child;
      struct cmpinfo cmp = stringcmp(word, parent->word, num);

      if (cmp.comp == 0) {
        break;
      }

      if (cmp.match && groupnumber == 0) {
        if (parent->gpnum == 0)
          parent->gpnum = groupnumber = ++groupnumbercounter;
        else
          groupnumber = parent->gpnum;
      }

      child = (cmp.comp < 0) ? &parent->left : &parent->right;

      if (*child == NULL) {
        *child          = tnode_new(word);
        (*child)->gpnum = groupnumber;
        break;
      }
      parent = *child;
    }
  }
  return root;
}

static void
tree_print(const struct tnode *node)
{
  if (node) {
    tree_print(node->left);
    if (node->gpnum > 0)
      printf("%u - %s\n", node->gpnum, node->word);
    tree_print(node->right);
  }
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

int
main(int argc, char *argv[])
{
  struct tnode *root;
  char word[200];
  int num;

  root = NULL;
  num  = (argc < 2) ? 6 : atoi(argv[1]);

  assert(num > 0);

  while (_getword(word, sizeof(word)) != EOF)
    if (isalpha(word[0]) || word[0] == '_')
      root = addtree(root, word, num);

  tree_print(root);

  return 0;
}
