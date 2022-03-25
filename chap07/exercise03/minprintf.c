/*
 * Exercise 7-3. Revise minprintf to handle more of the other
 * facilities of printf.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static void
minprintf(const char *fmt, ...)
{
  va_list ap;
  const char *p;

  va_start(ap, fmt);
  for (p = fmt; *p; ++p) {
    if (*p != '%') {
      putchar(*p);
    } else {
      char buffmt[10];
      char *wbuf = buffmt;

      for (*wbuf = *p; *wbuf; *++wbuf = *++p) {
        if (*wbuf == 'd') {
          *++wbuf = '\0';
          printf(buffmt, va_arg(ap, int));
        } else if (*wbuf == 'f') {
          *++wbuf = '\0';
          printf(buffmt, va_arg(ap, double));
        } else if (*wbuf == 's') {
          *++wbuf = '\0';
          printf(buffmt, va_arg(ap, char *));
        } else if (isalpha(*wbuf)) {
          *++wbuf = '\0';
          printf("%s", buffmt);
        } else {
          continue;
        }
        break;
      }
    }
  }
  va_end(ap);
}

int
main(void)
{
  minprintf("Boa noite, %.3s\n" , "gostosa");
  return 0;
}
