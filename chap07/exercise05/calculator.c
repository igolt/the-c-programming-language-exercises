/*
 * Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or
 * sscanf to do the input and number conversion.
 */
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include <cbook/iolib.h>
#include <cbook/utils.h>

typedef unsigned char uchar;

#define STACK_SIZE 100

static double stack[STACK_SIZE];
static double *stackp = stack;

#define STACK_END (stack + STACK_SIZE)

#define STACK_IS_EMPTY() (stackp == stack)
#define STACK_IS_FULL()  (stackp == STACK_END)

#define stack_push(num)                                                        \
  do {                                                                         \
    if (STACK_IS_FULL())                                                       \
      eputs("error: stack is full");                                           \
    else                                                                       \
      *stackp++ = (num);                                                       \
  } while (0)

static double
stack_pop(void)
{
  if (STACK_IS_EMPTY()) {
    eputs("error: stack is empty");
    return 0.0;
  }
  return *--stackp;
}

#define CASE_OP(op_char, op)                                                   \
  case op_char: {                                                              \
    double op2 = stack_pop();                                                  \
                                                                               \
    stack_push(stack_pop() op op2);                                            \
    break;                                                                     \
  }

#define ungetchar(c) ungetc((c), stdin)

int
main(void)
{
  char c;
  double num;

  while (scanf("%c", &c) == 1) {
    if (isblank((uchar) c))
      continue;
    if (c == '+' || c == '-') {
      char c2;

      if (scanf("%c", &c2) != 1)
        break;

      if (isdigit((uchar) c2)) {
        ungetchar((uchar) c2);
        if (scanf("%lf", &num) != 1)
          break;
        stack_push((c == '+') ? num : -num);
        continue;
      }
    } else if (isdigit((uchar) c)) {
      ungetchar((uchar) c);
      if (scanf("%lf", &num) != 1)
        break;
      stack_push(num);
      continue;
    }

    switch (c) {
      CASE_OP('+', +);
      CASE_OP('-', -);
      CASE_OP('*', *);

      case '/': {
        double op2 = stack_pop();

        if (op2 != 0)
          stack_push(stack_pop() / op2);
        else
          eputs("error: zero divisor");
        break;
      }

      case '%': {
        double op2 = stack_pop();

        stack_push(fmod(stack_pop(), op2));
        break;
      }

      case '\n':
        printf("\tResult: %.8g\n", stack_pop());
        break;

      default:
        eprintf("error: unknow command %c\n", c);
        break;
    }
  }
  return 0;
}
