#include <stdio.h>
#include "getch.c"

main()
{
	char str[4];
	int i, n;

	for(n = 0; n < 2; ++n)
	{
		for(i = 0; i < 3; i++)
			str[i] = getch();
		str[i] = '\0';
		printf("str%d: %s\n", n, str);

		for(i = 2; i >= 0; i--)
			ungetch(str[i]);
	}

}
