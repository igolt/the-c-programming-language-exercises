#ifndef IGOLT_STRING_H
#define IGOLT_STRING_H

#define strempty(s) ((s)[0] == '\0')

char *strdup(const char *s);

int strcasecmp(const char *s1, const char *s2);

char *strreverse(char *s);

#endif /* IGOLT_STRING_H */
