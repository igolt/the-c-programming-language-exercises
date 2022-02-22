/*
 * Exercise 5-20. Expand dcl to handle declarations with function arguments
 * types, qualifiers like const, and so on.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include <cbook/iolib.h>
#include <cbook/utils.h>
#include <cbook/strlib.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

static char out[1000];
static char name[MAXTOKEN];
static char datatype[MAXTOKEN];

static char token[MAXTOKEN];
static int  cachetoken = 0;
static int  tokentype  = 0;

static int  gettoken(void);
#define ungettoken() (cachetoken = 1)

static int dcl(void);
static int dirdcl(void);
static int dcl_specifiers(char *);

int
main(void)
{
  extern int tokentype;

  while (gettoken() != EOF) {
    out[0] = name[0] = datatype[0] = '\0';

    ungettoken();

    if (dcl_specifiers(datatype))
      break;

    dcl();
    if (tokentype != '\n') {
      eputs("syntax error");
      break;
    }
    printf("%s:%s%s\n", name, out, datatype);
  }
  return 0;
}

static int
gettoken(void)
{
  extern int cachetoken;
  extern char token[];
  int c;
  char *wp = token;

  if (cachetoken) {
    cachetoken = 0;
    return tokentype;
  }

  while ((c = getch()) == ' ' || c == '\t')
    continue;

  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    if (c != EOF)
      ungetch(c);

    token[0] = '(';
    token[1] = '\0';

    return tokentype = '(';
  }

  if (c == '[') {
    for (*wp++ = c; (c = getch()) != EOF;)
      if ((*wp++ = c) == ']')
        break;
    *wp              = '\0';
    return tokentype = (c == ']') ? BRACKETS : *--wp;
  }

  if (isalpha(c) || c == '_') {
    do {
      *wp++ = c;
    } while (isalnum(c = getch()) || c == '_');
    *wp = '\0';
    if (c != EOF)
      ungetch(c);
    return tokentype = NAME;
  }
  token[0] = c;
  token[1] = '\0';

  return tokentype = c;
}

/* Test if token is a type qualifiers or a storage class */
static int
issctq(const char *token)
{
  static const char *const storaclass_typequalifies[] = {
    "auto",
    "const",
    "extern",
    "register",
    "static",
    "volatile"
  };
  size_t high = ARRAYSIZE(storaclass_typequalifies);
  size_t low  = 0, mid;

  while (high > low) {
    int cmp;
    mid = (low + high) / 2;

    cmp = strcmp(token, storaclass_typequalifies[mid]);

    if (cmp == 0) {
      return 1;
    } else if (cmp > 0) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }

  return 0;
}

static int
dcl(void)
{
  extern char out[];
  unsigned ns;

  for (ns = 0; gettoken() == '*'; ++ns)
    continue;

  if (dirdcl())
    return 1;

  while (ns) {
    strcat(out, " pointer to");
    --ns;
  }
  return 0;
}

static int
dirdcl(void)
{
  extern int  tokentype;
  extern char out[];
  char temp[100];

  if (tokentype == '(') {
    dcl();
    if (tokentype != ')') {
      eputs("error: missing )");
      return 1;
    }
  } else if (tokentype == NAME) {
    if (strempty(name))
      strcpy(name, token);
  } else {
    eputs("error: expected name or (dcl)");
    return 1;
  }

  while (1) {
    gettoken();

    if (tokentype == PARENS) {
      strcat(out, " function returning");
    } else if (tokentype == BRACKETS) {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    } else if (tokentype == '(') {
      strcat(out, " function receiving");
      while (1) {
        temp[0] = '\0';
        dcl_specifiers(temp);
        dcl();
        strcat(out, temp);
        if (tokentype != ',') {
          break;
        }
        strcat(out, ",");
      }
      if (tokentype != ')') {
        eputs("error: expected )");
      }
      strcat(out, " and returning");
    } else {
      break;
    }
  }
  return 0;
}

static int
dcl_specifiers(char *dest)
{
  unsigned tokens;
  int found_datatype = 0;

  for (tokens = 0; gettoken() != EOF; ++tokens) {
    if (tokentype != NAME) {
      break;
    } else {
      /* Test if token is a type-specifier */
      if (!issctq(token)) {
        if (found_datatype) break;
        found_datatype = 1;
      }
      strcat(dest, " ");
      strcat(dest, token);
    }
  }
  if (tokens == 0) {
    eputs("Error: expected qualifiers or type-specifier");
    return 1;
  }
  ungettoken();
  return 0;
}
