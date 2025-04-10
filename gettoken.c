#include "getch.h"
#include "gettoken.h"
#include <ctype.h>
#include <string.h>
#include "contains.h"

int tokentype; 			/* type of last token */
char token[MAXTOKEN];		/* last token string */

/* gettoken: return next token */
int gettoken(void)
{
	int c; /*getch(void);
	void ungetch(int); */
	char *p = token;
	/* just some of the data types there are many more */
	static const char *datatypes[] = {
		"int", "char", "bool", "float", "double", 
		"short", "long", "int8_t", "int16_t",
		"int32_t", "int64_t", "uint8_t", "uint16_t",
		"uint32_t", "uint64_t", "int_least8_t", 
		"int_least16_t", "int_least32_t", 
		"int_least64_t", "uint_least8_t", "uint_least16_t",
		"uint_least32_t", "uint_least64_t", 
		"int_fast8_t", "int_fast16_t", "int_fast32_t", 
		"int_fast64_t", "uint_fast8_t", "uint_fast16_t",
		"uint_fast32_t", "uint_fast64_t"
	};

	while((c = getch()) == ' ' || c == '\t')
		;
	if(c == '(')
	{
		if((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		/* test if there what is inside isn't a dcl but function parameters */
		int i;
		for(*p++ = c, i = 1; isalpha(c = getch()); ++i)
			*p++ = c;
		ungetch(c);
		*p = '\0';
		/* check if it's a datatype. If so we have a function parameter, not a dcl */
		if(contains((void*) token, (void*) datatypes, 1, 
	   	   sizeof(datatypes)/sizeof(char*), sizeof(char), (int (*)(void*, void*))(*streq)))
		{
			/* get rest of function parameters */
			while((c = getch()) != ')')
				*p++ = c;
			*p = '\0';
			return tokentype = PARAMS;
		}
		/* it's not function parameters, rewind what we did above if statement */
		else
		{
			while(i-- > 0)
			{
				ungetch(*p--);
			}
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
