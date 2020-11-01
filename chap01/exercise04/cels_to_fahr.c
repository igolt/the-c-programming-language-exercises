/*
 * Exercise 1-4. Write a program to print the corresponding Celsius to
 * Fahrenheit table.
 */
#include <stdio.h>

#define LOWER_LIMIT -17.8
#define UPPER_LIMIT 148.9
#define STEP 20 * (5.0/9)

int main()
{
	double celsius;

	printf("------------------------\n");
	printf("| Fahrenheit | Celsius |\n");
	printf("------------------------\n");
	for (celsius = LOWER_LIMIT; celsius <= UPPER_LIMIT; celsius += STEP)
		printf("| %10.1lf | %7.1lf |\n", celsius * (9.0/5) + 32, celsius);
	printf("------------------------\n");
	return 0;
}
 
