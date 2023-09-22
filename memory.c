#include "shell.h"

/**
 * bfree - it frees the pointer and NULLs the address
 * @ptr: the Address of the pointer to free
 *
 * Return: returns 1 if freed, and 0 otherwise
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
