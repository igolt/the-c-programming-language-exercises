/*
 * Exercise 3-5. Write the function itob(n,s,b) that converts the integer
 * n into a base b character representation in the string s. In particular,
 * itob(n,s,16) formats s as a hexadecimal integer in s.
 */

#include <stdio.h>
#include <string.h>

int myabs(int);
char *reverse(char *);
char *itob(int, char *, int);

int main()
{
	int base = 8, num = 9;
	char result[30];

	printf("Num: %d\n", num);
	printf("Base: %d\n", base);
	printf("itob: %s\n", itob(num, result, base));
	return 0;
}

int myabs(int num)
{
	return (num < 0) ? (num * (-1)) : num;
}

char *reverse(char *s)
{
	int i, j;
	char temp;

	for (i = 0, j = strlen(s) - 1; i < j; ++i, --j)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
	return s;
}

char *itob(int n, char *s, int b)
{
	int i, temp;
	char sign;

	sign = (n < 0) ? '-' : '+';

	i = 0;
	do
	{
		temp = myabs(n % b);
		s[i++] = (temp > 10) ? (temp + 'a' - 10) : temp + '0';
	} while ((n /= b));

	if (sign == '-')
		s[i++] = '-';
	s[i] = '\0';
	return reverse(s);
}
