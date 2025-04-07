#include <stdio.h>
#include <string.h>
#include "gettoken.h"

#define MAXOUT		1000

void dcl(void);
void dirdcl(void);
int gettoken(void);

char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN]; 	/* data type = char, int, etc. */
char out[MAXOUT];		/* output string */

int main(void) /* convert declarations to words */
{
	/* 1st token on line is the datatype */
	while(gettoken() != EOF) 
	{
		strcpy(datatype, token);
		out[0] = '\0';
		dcl(); /* parse rest of line */
		if(tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;

	for(ns = 0; gettoken() == '*'; ) /* count *'s */
		ns++;
	dirdcl();
	while(ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;

	if(tokentype == '(') /* ( dcl ) */
	{
		dcl();
		if(tokentype != ')')
			printf("error: missing )\n");
	}
	else if(tokentype == NAME) /* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while((type=gettoken()) == PARENS || type == BRACKETS)
		if(type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}

}
