#ifndef IO_LIB_H
#define IO_LIB_H

int eprint(const char *s);

int eputs(const char *s);

int eprintf(const char *fmt, ...);

int getch(void);

int ungetch(int c);

#endif /* IO_LIB_H */
