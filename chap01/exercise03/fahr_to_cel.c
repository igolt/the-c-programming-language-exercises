/*
 * Exercise 1-3. Modify the temperature conversion program
 * to print a heading above the table.
 */
#include <stdio.h>

#define LOWER_LIMIT 0
#define UPPER_LIMIT 300
#define STEP        20

int
main(void)
{
  int fahr;

  printf("------------------------\n");
  printf("| Fahrenheit | Celsius |\n");
  printf("------------------------\n");
  for (fahr = LOWER_LIMIT; fahr <= UPPER_LIMIT; fahr += STEP)
    printf("| %10d | %7.1f |\n", fahr, (5.0 / 9) * (fahr - 32));
  printf("------------------------\n");
  return 0;
}
