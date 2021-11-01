/*
 * Exercise 4-6. Add commands for handling variables. (It's
 * easy to provide twenty-six variables with single letter
 * names.) Add a variable for the most recentry printed value.
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <cbook/iolib.h>

#define MAXOP  100
#define NUMBER '0'

int getop(char *);
void stack_push(double);
double stack_pop(void);

int
main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        stack_push(atof(s));
        break;

      case '+':
        stack_push(stack_pop() + stack_pop());
        break;

      case '*':
        stack_push(stack_pop() * stack_pop());
        break;

      case '-':
        op2 = stack_pop();
        stack_push(stack_pop() - op2);
        break;

      case '/':
        op2 = stack_pop();
        if (op2 != 0.0)
          stack_push(stack_pop() / op2);
        else
          puts("error: zero divisor");
        break;

      case '%':
        op2 = stack_pop();
        stack_push(fmod(stack_pop(), op2));
        break;

      case '\n':
        printf("\tResult: %.8g\n", stack_pop());
        break;

      default:
        eprintf("error: unknow command %s\n", s);
        break;
    }
  }
  return 0;
}

#define MAXVAL 100

double stack[MAXVAL];
int sp = 0;

void
stack_push(double f)
{
  if (sp < MAXVAL)
    stack[sp++] = f;
  else
    eprintf("error: stack full, can't push %g\n", f);
}

double
stack_pop(void)
{
  if (sp > 0)
    return stack[--sp];
  else {
    fputs("error: stack empty", stderr);
    return 0.0;
  }
}

int
getop(char *s)
{
  size_t i = 0;
  int c;

  while ((s[i] = c = getch()) == ' ' || c == '\t')
    /* Do nothing */;

  if (c == '-' || c == '+')
    s[++i] = c = getch();
  if (!isdigit(c) && c != '.' && c != 'e' && c) {
    s[++i] = '\0';
    if (i > 1 && c != EOF)
      ungetch(c);
    return s[0];
  }

  while (isdigit(c))
    s[++i] = c = getch();
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == 'e' || c == 'E') {
    s[++i] = c = getch();
    if (c == '-' || c == '+' || isdigit(c))
      while (isdigit(s[++i] = c = getchar()))
        ;
  }
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}
