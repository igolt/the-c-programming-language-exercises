/*
 * Exercise 4-2. Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent.
 */

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

double myatof(const char *s);

int
main(void)
{
  assert(123.45e-6 == myatof("123.45e-6"));
  assert(-57e1 == myatof("-57e1"));
  assert(-57 == myatof("-57e 1"));
  return 0;
}

int myatoi(const char *s);

double
myatof(const char *s)
{
  double val;
  short int sign;

  while (isspace(*s))
    ++s;

  sign = (*s == '-') ? -1 : 1;

  if (*s == '+' || *s == '-')
    ++s;

  for (val = 0.0; isdigit(*s); ++s)
    val = val * 10 + *s - '0';

  if (*s == '.') {
    double f;

    for (f = 0.1, ++s; isdigit(*s); f /= 10, ++s)
      val += (*s - '0') * f;
  }
  if (*s == 'e' || *s == 'E')
    val *= pow(10, myatoi(++s));
  return val * sign;
}

int
myatoi(const char *s)
{
  int val;
  short int sign;

  sign = (*s == '-') ? -1 : 1;

  if (*s == '+' || *s == '-')
    ++s;

  for (val = 0; isdigit(*s); ++s)
    val = val * 10 + *s - '0';

  return val * sign;
}
