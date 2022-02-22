/*
 * 5-18. Make dcl recover from input errors.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cbook/iolib.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

static void dcl(void);
static void dirdcl(void);

static int gettoken(void);

static int tokentype;
static char token[MAXTOKEN];
static char name[MAXTOKEN];
static char datatype[MAXTOKEN];
static char out[1000];

int
main(void)
{
  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if (tokentype != '\n')
      eputs("syntax error");
    printf("%s: %s %s\n", name, out, datatype);
  }
  return 0;
}

static void
dcl(void)
{
  int ns;

  for (ns = 0; gettoken() == '*'; ++ns)
    continue;

  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

static void
dirdcl(void)
{
  int type;

  if (tokentype == '(') {
    dcl();
    if (tokentype != ')')
      eputs("error: missing )");
  } else if (tokentype == NAME)
    strcpy(name, token);
  else
    eputs("error: expected name or (dcl)");

  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

static int
gettoken(void)
{
  int c;
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    continue;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    *p++ = c;
    while ((*p++ = getch()) != ']')
      continue;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch()); )
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }
  return tokentype = c;
}
