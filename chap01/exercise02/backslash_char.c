/*
 * Exercise 1-2. Experiment to find out what happens when print's arguments
 * string constains \c, where c is some character no listed above.
 */
#include <stdio.h>

int
main(void)
{
  printf("\\a: Before\aAfter\n");
  printf("\\b: Before\bAfter\n");
  /* printf("\\e: Before\eAfter\n"); */
  printf("\\f: Before\fAfter\n");
  printf("\\n: Before\nAfter\n");
  printf("\\r: Before\rAfter\n");
  printf("\\t: Before\tAfter\n");
  printf("\\v: Before\vAfter\n");
  return 0;
}
