/* 
 * Exercise 1-15. Rewrite the temperature conversion program
 * of Section 1.2 to use a function for conversion.
 */
#include <stdio.h>

#define LOWER_LIMIT 0
#define UPPER_LIMIT 300
#define STEP 20

double fahr_to_cels(double fahr)
{
	return (5.0/9) * (fahr-32);
}

int main()
{
	int fahr;

	printf("------------------------\n");
	printf("| Fahrenheit | Celsius |\n");
	printf("------------------------\n");
	for (fahr = LOWER_LIMIT; fahr <= UPPER_LIMIT; fahr += STEP)
		printf("| %10d | %7.1lf |\n", fahr, fahr_to_cels(fahr));
	printf("------------------------\n");
	return 0;
}

