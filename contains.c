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
