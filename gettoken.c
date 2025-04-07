#include "getch.h"
#include "gettoken.h"
#include <ctype.h>
#include <string.h>

int tokentype; 			/* type of last token */
char token[MAXTOKEN];		/* last token string */

/* gettoken: return next token */
int gettoken(void)
{
	int c; /*getch(void);
	void ungetch(int); */
	char *p = token;

	while((c = getch()) == ' ' || c == '\t')
		;
	if(c == '(')
	{
		if((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[')
	{
		for(*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c))
	{
		for(*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}
