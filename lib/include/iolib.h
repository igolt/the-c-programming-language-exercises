#ifndef IGOLT_IO_LIB_H
#define IGOLT_IO_LIB_H

#include <stdio.h>

/* Convenient functions to write to stderr */
#define eprint(s) fputs(s, stderr)
#define eputs(s) fputs(s "\n", stderr)
int eprintf(const char *fmt, ...);

int getch(void);

int ungetch(int c);

int fgetline(char *line, int max, FILE *stream);
#define getline(line, max) fgetline(line, max, stdin)

char *fgetword(char *word, int size, FILE *stream);
#define getword(word, size) fgetword(word, size, stdin)

#endif /* IGOLT_IO_LIB_H */
