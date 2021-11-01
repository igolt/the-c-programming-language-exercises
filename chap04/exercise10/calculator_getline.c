/*
 * Exercise 4-10. An alternative organization uses getline to read an entire
 * input line; this makes getch and ungetch unnecessary. Revise the calculator
 * to use this approach.
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <cbook/iolib.h>

#define MAXOP 100

#define NUM '0'

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
      case NUM:
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

int
getop(char *s)
{
#define GETCHAR() (*it++)
  static char line[MAXOP] = "\0";
  static char *it         = line;

  int c;
  size_t i = 0;

  if (*it == '\0') {
    it = line;
    if (getline(line, MAXOP) == 0)
      return EOF;
  }

  while ((*s = c = GETCHAR()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;
  i = 0;
  while (isdigit(c))
    s[++i] = c = GETCHAR();

  if (c == '.')
    while (isdigit(s[++i] = c = GETCHAR()))
      ;
  s[i] = '\0';
  --it;
  return NUM;
#undef GETCHAR
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
    eputs("error: stack empty");
    return 0.0;
  }
}
