#include "gettoken.h"
#include <stdio.h>
#include <string.h>

#define MAXOUT		1000

char out[MAXOUT];		/* output string */

/* undcl: convert word description to declaration */
int main(void)
{
	int type;
	char temp[MAXTOKEN];

	int ptr = 0;

	while(gettoken() != EOF)
	{
		strcpy(out, token);
		while((type = gettoken()) != '\n')
			if(type == PARENS || type == BRACKETS)
			{
				if(ptr)
				{
					sprintf(temp, "(%s)", out);
					strcpy(out, temp);
					ptr = 0;
				}
				strcat(out, token);
			}
			else if(type == '*')
			{
				sprintf(temp, "*%s", out);
				strcpy(out, temp);
				ptr = 1;
			}
			else if(type == NAME)
			{
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
				printf("invalid input at %s\n", token);
		printf("%s\n", out);
	}
	return 0;
}
