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

	assert(month_day(2021, 35, &month, &day) != -1);
	assert(month == FEB && day == 4);
	assert(month_day(2021, 35, NULL, &day) == -1);

	assert(month_day(2021, 365, &month, &day) != -1);
	assert(month == DEC && day == 31);

	assert(month_day(2020, 366, &month, &day) != -1);
	assert(month == DEC && day == 31);
	return 0;
}

typedef char int8_t;

int8_t daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
};

int is_leap(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int day_of_year(int year, int month, int day)
{
	int8_t *dtab;

	if (year < 0 || month < JAN || month > DEC
		|| day < 1 || day > (dtab = daytab[is_leap(year)])[month])
		return -1;

	while (--month)
		day += *++dtab;
	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;
	int8_t *dtab;

	if (year < 0 || yearday < 1
		|| yearday > ((leap=is_leap(year)) ? 366: 365)
		|| pmonth == NULL || pday == NULL)
		return -1;

	dtab = daytab[leap];
	while (yearday > *++dtab)
		yearday -= *dtab;
	*pday = yearday;
	*pmonth = dtab - daytab[leap];
	return 0;
}
