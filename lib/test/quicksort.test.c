#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "quicksort.h"

#define print_array(fmt, array, array_size) \
  do                                        \
  {                                         \
    size_t i = 0;                           \
                                            \
    while (i < array_size)                  \
      printf(fmt, array[i++]);              \
  } while (0)

void test_sort_random_integer_array(void);
void test_sort_2_integers_array(void);
void test_sort_integer_array(void);
void test_sort_strings_array(void);

int main(void)
{
  test_sort_2_integers_array();
  test_sort_integer_array();
  test_sort_strings_array();
  return 0;
}

void assert_order(const void *first, size_t n, size_t size, compfunc_t comp)
{
  if (n > 1)
  {
    char *after = (char *) first + size;
    char *end = (char *) first + (size * n);

    while (after < end)
    {
      char *before = after - size;

      assert((*comp)(before, after) <= 0);
      after += size;
    }
  }
}

int _intcmp(int i1, int i2)
{
  if (i1 > i2)
    return 1;
  if (i1 == i2)
    return 0;
  return -1;
}

int intcmp(const void *p1, const void *p2)
{
  int i1 = *(const int *) p1;
  int i2 = *(const int *) p2;

  return _intcmp(i1, i2);
}

void test_sort_2_integers_array(void)
{
  int array[] = { 2, 1 };
  size_t array_size = sizeof(array) / sizeof(*array);

  printf("Before sorting: ");
  print_array("%d ", array, array_size);
  putchar('\n');

  quicksort((void *) array, array_size, sizeof(*array), intcmp);
  assert_order((const void *) array, array_size, sizeof(*array), intcmp);

  printf("After sorting: ");
  print_array("%d ", array, array_size);
  puts("\n");
}

void test_sort_integer_array(void)
{
  int array[] = { 9, -15, 43, -50, 100, 30 };
  size_t array_size = sizeof(array) / sizeof(*array);

  printf("Before sorting: ");
  print_array("%d ", array, array_size);
  putchar('\n');

  quicksort((void *) array, array_size, sizeof(*array), intcmp);

  printf("After sorting: ");
  print_array("%d ", array, array_size);
  puts("\n");

  assert_order((const void *) array, array_size, sizeof(*array), intcmp);
}

int stringcmp(const void *p1, const void *p2)
{
  const char *s1 = *(const char **) p1;
  const char *s2 = *(const char **) p2;

  return strcmp(s1, s2);
}


void test_sort_strings_array(void)
{
  const char *strings[] = {
    "Zetha",
    "Hello world",
    "Makefile",
    "GNU core utils",
    "Linux Kernel",
    "The C++ Programming Language",
    "main.c",
    "$ Money",
    ""
  };
  size_t array_size = sizeof(strings) / sizeof(*strings);

  puts("Before sorting:");
  print_array("`%s`\n", strings, array_size);
  putchar('\n');

  quicksort((void *) strings, array_size, sizeof(*strings), stringcmp);

  puts("After sorting:");
  print_array("`%s`\n", strings, array_size);

  assert_order((const void *) strings, array_size, sizeof(*strings), stringcmp);
}

#define MAX_SIZE 500

void test_sort_random_integer_array(void)
{
  int array[MAX_SIZE];
  size_t i;

  srand(time(NULL));

  for (i = 0; i < MAX_SIZE; ++i)
    array[i] = rand() % MAX_SIZE;

  puts("Before sorting:");
  print_array("%d\n", array, MAX_SIZE);
  putchar('\n');

  quicksort((void *) array, MAX_SIZE, sizeof(*array), intcmp);

  puts("After sorting:");
  print_array("%d\n", array, MAX_SIZE);

  assert_order((void *) array, MAX_SIZE, sizeof(*array), intcmp);

  putchar('\n');
}
