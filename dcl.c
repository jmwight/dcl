#include <stdio.h>
#include <string.h>
#include "gettoken.h"
#include "getch.h"
#include "contains.h"

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
		datatype[0] = '\0'; /* clear string */
		while(tokentype == '\n') /* skip over blank lines */
			gettoken();
		/* scan for possible qualifers */
		static const char *qualifiers[] = {"const", "static", "unsigned", "signed", "volatile", "register", "auto"};
		for( ; contains((void*) token, (void*) qualifiers, 1, 7, sizeof(char), (int (*)(void*, void*))(streq)); gettoken())
		{
			strcat(datatype, token);
			datatype[strlen(datatype) + 1] = '\0';
			datatype[strlen(datatype)] = ' ';
		}


		strcat(datatype, token);
		out[0] = '\0';
		dcl(); /* parse rest of line */
		if(tokentype != '\n')
		{
			printf("syntax error\n");
			/* skip over rest of line */
			while(getch() != '\n')
				;
		}
		else
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
		else if(type == PARAMS)
			strcat(out, " function with parameters (%s) returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}

}
