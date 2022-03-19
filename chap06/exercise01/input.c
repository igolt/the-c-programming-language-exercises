/**
 * This is a input test for getword.c
 */
#include <stdio.h>

#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int
main(void)
{
  int i;
  const char *keywords[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "unsigned",
    "void",
    "volatile",
    "while",
  };
  /* const array size */
  const unsigned arrsize = ARRAYSIZE(keywords);

  for (i = 0; (unsigned) i < arrsize; ++i) {
    puts(keywords[i]);
  }
  return 0;
}
