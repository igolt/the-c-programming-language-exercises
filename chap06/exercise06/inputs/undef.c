#include <stdio.h>

#define MAX 100

int
main(void)
{
  char buff[MAX];

#undef MAX

  fgets(buff, MAX, stdin);

  fputs(buff, stdout);
  return 0;
}
