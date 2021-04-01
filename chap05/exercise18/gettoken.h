#ifndef GET_TOKEN_H
#define GET_TOKEN_H

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

extern int tokentype;             /* type of last token */
extern char token[MAXTOKEN];      /* last token string */

int gettoken(void);

#endif /* GET_TOKEN_H */
