#include <stdio.h>
#include <string.h>
#include "gettoken.h"
#include "getch.h"

#define MAXOUT		1000

void dcl(void);
void dirdcl(void);
int gettoken(void);
int contains(void *el, void *a, int layers, size_t nmem, size_t width, int (*match)(void *, void *));
int streq(char *s0, char **s1);

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
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}

}

int contains(void *el, void *a, int layers, size_t nmem, size_t width, int (*eqcomp)(void *, void *))
{
	while(nmem-- > 0)
	{
		/* layers is a workaround. If it's pointer to an array of pointers to strings. An just a pointer to an array of ints.
		 * It's a bit of a creative solution I think */
		/* only one dereference to get to a data element */
		if(layers == 0)
		{
			if((*eqcomp)(el, (void *)a+nmem*width))
				return 1;
		}
		/* two layers of dereferencing to get to data element */
		else if(layers == 1)
		{
			if((*eqcomp)(el, (void **)a+nmem*width))
				return 1;
		}
		/* three layers of dereferencing to get to data element */
		else if(layers == 2)
		{
			if((*eqcomp)(el, (void ***)a+nmem*width))
				return 1;
		}
		else
		{
			printf("Error: invalid number of layers\n");
			return 0;
		}
			

	}
	return 0;
}

/* streq: check if two strings are equal. If they are return 1, if not return 0 */
int streq(char *s0, char **s1)
{
	if(strcmp(s0, *s1) == 0)
		return 1;
	else
		return 0;
}
