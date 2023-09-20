#include "shell.h"

/**
 * bfree - it frees a pointer and nULLs the address
 * @ptr: The address of  pointer to free
 *
 * Return: returns 1 if freed, and 0 otherwise .
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

