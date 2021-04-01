#include <stdio.h>
#include <assert.h>

enum months {
	JAN = 1, FEB, MAR, APR, MAY, JUN,
	JUL, AUG, SEP, OCT, NOV, DEC
};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
	int month, day;

	assert(day_of_year(2021, FEB, 4) == 35);
	assert(day_of_year(2021, FEB, 28) == 59);
	assert(day_of_year(2020, FEB, 29) == 60);
	assert(day_of_year(2020, DEC, 31) == 366);
	assert(day_of_year(2021, DEC, 31) == 365);

	assert(day_of_year(2021, 0, 4) == -1);
	assert(day_of_year(2021, 13, 4) == -1);
	assert(day_of_year(2021, FEB, 29) == -1);
	assert(day_of_year(2021, FEB, 29) == -1);

	month_day(2021, 35, &month, &day);
	assert(month == FEB && day == 4);
	assert(month_day(2021, 35, NULL, &day) == -1);

	assert(month_day(2021, 365, &month, &day) != -1);
	assert(month == DEC && day == 31);

	assert(month_day(2020, 366, &month, &day) != -1);
	assert(month == DEC && day == 31);
	return 0;
}

char daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int is_leap(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int day_of_year(int year, int month, int day)
{
	int leap, i;

	if (year < 0 || month < JAN || month > DEC
		|| day < 1 || day > daytab[(leap=is_leap(year))][month])
		return -1;

	for (i = JAN; i < month; ++i)
		day += daytab[leap][i];
	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;

	if (pmonth == NULL || pday == NULL || year < 0
			|| yearday < 1 || yearday > ((leap=is_leap(year)) ? 366: 365))
		return -1;

	for (*pmonth = JAN; yearday > daytab[leap][*pmonth]; ++*pmonth)
		yearday -= daytab[leap][*pmonth];
	*pday = yearday;
	return 0;
}
