/*
 * 5-18. Make dcl recover from input errors.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "gettoken.h"
#include "iolib.h"

enum
{ 
	SUCESS = 0,
	SYNTAX_ERROR,
	UNEXPECTED_TOKEN,
	MISSING_PAREN
};

const char *error_msgs[] = {
	"No error",
	"syntax error",
	"expected name or (dcl)",
	"missing )"
};

int dcl(void);
int dirdcl(void);
void clear_err(void);

char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc. */
char out[1000];

int main(void)
{
	while (gettoken() != EOF)
	{
		int status;

		strcpy(datatype, token);
		out[0] = '\0';
		status = dcl();

		if (status == SUCESS && tokentype != '\n')
			status = SYNTAX_ERROR;
		if (status == SUCESS)
			printf("%s: %s %s\n", name, out, datatype);
		else
		{
			eprintf("%s\n", error_msgs[status]);
			clear_err();
		}
	}
	return 0;
}

int dcl(void)
{
	int ns;
	int status;

	for (ns = 0; gettoken() == '*'; )
		++ns;

	status = dirdcl();
	if (status != SUCESS)
		return status;
	while (ns-- > 0)
		strcat(out, " pointer to");
	return SUCESS;
}

int dirdcl(void)
{
	int type;

	if (tokentype == '(')
	{
		dcl();
		if (tokentype != ')')
			return MISSING_PAREN;
	}
	else if (tokentype == NAME)
		strcpy(name, token);
	else
		return UNEXPECTED_TOKEN;

	while ((type = gettoken()) == PARENS || type == BRACKETS)
	{
		if (type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
	return SUCESS;
}

void clear_err(void)
{
	while (tokentype != '\n' && tokentype != EOF)
		gettoken();
}
