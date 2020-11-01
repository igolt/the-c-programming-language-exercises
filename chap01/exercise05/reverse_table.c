/*
 * Exercise 1-5. Modify the temperature conversion program to print the table
 * in reverse order, that is, from 300 degrees to 0.
 */
#include <stdio.h>

#define UPPER_LIMIT 300
#define LOWER_LIMIT 0
#define STEP 20

double fahr_to_cels(double fahrenheit)
{
	return (5.0/9) * (fahrenheit-32);
}

int main()
{
	double fahr;

	for (fahr = UPPER_LIMIT; fahr >= LOWER_LIMIT; fahr -= STEP)
		printf(" %3.0lf %6.1lf\n", fahr, fahr_to_cels(fahr));
	return 0;
}
