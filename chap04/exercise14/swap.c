/*
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments
 * of type t. (Block structure will help.)
 */

#include <stdio.h>

#define swap(t, x, y) { t __temp__ = (x); (x) = (y); (y) = __temp__; }

int main(void)
{
	int x = 10, y = 20;
	double z = 29.4, w = 41.342;

	printf("x: %d, x: %d\n", x, y);
	swap(int, x, y);
	printf("x: %d, x: %d\n\n", x, y);

	printf("z: %g, w: %g\n", z, w);
	swap(double, z, w);
	printf("z: %g, w: %g\n", z, w);
	return 0;
}
