/*
 * Exercise 7-4. Write a private version of scanf analogous to minprintf from
 * the previous section.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

static void
minscanf(const char *fmt, ...)
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
          scanf(buffmt, va_arg(ap, int *));
        } else if (*wbuf == 'f') {
          *++wbuf = '\0';
          scanf(buffmt, va_arg(ap, float *));
        } else if (*wbuf == 's') {
          *++wbuf = '\0';
          scanf(buffmt, va_arg(ap, char *));
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
  int n;
  float f;

  minscanf("%d%f", &n, &f);

  printf("n: %d\n", n);
  printf("f: %g\n", f);
  return 0;
}
