/*
 * Exercise 5-20. Expand dcl to handle declarations with function arguments
 * types, qualifiers like const, and so on.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 1000

typedef int bool;

enum { NAME, PARENS, BRACKETS };

char identifier[MAXTOKEN];
char datatype[MAXTOKEN];
char token[MAXTOKEN];
char out[1000];
int tokentype;

int gettoken(void);
void declaration(void);
void declarator(void);
void direct_declarator(void);
void pointer_handler(void);

int
gettoken(void)
{
  extern char token[];
  extern int tokentype;
  char *p = token;
  int c;

  while ((c = getchar()) == ' ' || c == '\t') {
    /* Jump white spaces bruh */;
  }

  if (c == '(') {
    if ((c = getchar()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    ungetc(c, stdin);
    return tokentype = '(';
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getchar()) != ']';)
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (c == '_' || isalpha(c)) {
    for (*p++ = c; (c = getchar()) == '_' || isalnum(c);)
      *p++ = c;
    *p = '\0';
    ungetc(c, stdin);
    return tokentype = NAME;
  }
  return tokentype = c;
}

void
declaration(void)
{
  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    declarator();
    if (tokentype != '\n') {
      /* error */
    }
    printf("%s:%s %s\n", identifier, out, datatype);
  }
}

void
declarator(void)
{
  if (gettoken() == '*') {
    pointer_handler();
  }
  direct_declarator();
}

void
direct_declarator(void)
{
  int type;

  if (tokentype == '(') {
    declarator();
    if (tokentype != ')') {
      /* error */
    }
  } else if (tokentype == NAME) {
    strcpy(identifier, token);
  } else {
    /* error */
  }

  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

void
pointer_handler(void)
{
  char tmp_buf[22];
  bool is_const;
  bool is_volatile;

  while (tokentype == '*') {
    is_volatile = is_const = 0;

    while (gettoken() == NAME) {
      if (strcmp(token, "const") == 0) {
        is_const = 1;
      } else if (strcmp(token, "volatile") == 0) {
        is_volatile = 1;
      } else {
        break;
      }
    }
    sprintf(tmp_buf, " %s%spointer to", is_const ? "constant " : "",
            is_volatile ? "volatile " : "");
    strcat(out, tmp_buf);
  }
}

int
main(void)
{
  declaration();
  return 0;
}
