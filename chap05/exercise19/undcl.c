/*
 * 5-19. Modify undcl so that it does not add reduntant parentheses to
 * declarations
 */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "../exercise18/gettoken.h"
#include <cbook/iolib.h>

char out[1000];

int
main(void)
{
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != EOF) {
      if (type == PARENS || type == BRACKETS)
        strcat(out, token);
      else if (type == '*')
        sprintf(temp, "(%s)", out);
      else if (type == NAME)
        sprintf(temp, "%s %s", token, out);
      else
        eprintf("Invalid input at %s\n", token);
    }
  }
  return 0;
}
