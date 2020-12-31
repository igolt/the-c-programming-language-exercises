
char *reverse(char *s)
{
	char *b, *e;

	for (e = s; *e; ++e)
		/* Do nothing */;
	for (b = s, --e; b < e; ++b, --e)
	{
		char temp = *b;
		*b = *e;
		*e = temp;
	}
	return s;
}
