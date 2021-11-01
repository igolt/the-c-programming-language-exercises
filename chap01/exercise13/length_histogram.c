/*
 * Exercise 1-13. Write a program to print a histogram of the lengths
 * of words in its input. It is easy to draw the histogram with the bars
 * horizontal; a vertical orientation is more challenging.
 */
#include <ctype.h>
#include <stdio.h>

int
main(void)
{
  char c;
  unsigned wordlen = 0, aux;

  while ((c = getchar()) != EOF) {
    if (isspace(c)) {
      if (wordlen != 0) {
        printf("%3u: ", wordlen);
        for (aux = 0; aux < wordlen; ++aux)
          putchar('|');
        putchar('\n');
        wordlen = 0;
      }
    } else
      ++wordlen;
  }
  return 0;
}
