#include "shell.h"

/**
 * CUSTOM_strncpy - Custom string copying function
 * @custom_dest: The destination string to copy to
 * @custom_src: The source string
 * @custom_n: The number of characters to copy
 * Return: The modified destination string
 */
char *CUSTOM_strncpy(char *custom_dest, char *custom_src, int custom_n)
{
	int custom_i, custom_j;
	char *custom_s = custom_dest;

	custom_i = 0;
	while (custom_src[custom_i] != '\0' && custom_i < custom_n - 1)
	{
		custom_dest[custom_i] = custom_src[custom_i];
		custom_i++;
	}
	if (custom_i < custom_n)
	{
		custom_j = custom_i;
		while (custom_j < custom_n)
		{
			custom_dest[custom_j] = '\0';
			custom_j++;
		}
	}
	return (custom_s);
}

/**
 * CUSTOM_strncat - Custom string concatenation function
 * @custom_dest: The first string
 * @custom_src: The second string
 * @custom_n: The maximum number of bytes to use
 * Return: The concatenated string
 */
char *CUSTOM_strncat(char *custom_dest, char *custom_src, int custom_n)
{
	int custom_i, custom_j;
	char *custom_s = custom_dest;

	custom_i = 0;
	custom_j = 0;
	while (custom_dest[custom_i] != '\0')
		custom_i++;
	while (custom_src[custom_j] != '\0' && custom_j < custom_n)
	{
		custom_dest[custom_i] = custom_src[custom_j];
		custom_i++;
		custom_j++;
	}
	if (custom_j < custom_n)
		custom_dest[custom_i] = '\0';
	return (custom_s);
}

/**
 * CUSTOM_strchr - Custom character search function
 * @custom_s: The string to search
 * @custom_c: The character to look for
 * Return: A pointer to the found character in the string
 */
char *CUSTOM_strchr(char *custom_s, char custom_c)
{
	do {
		if (*custom_s == custom_c)
			return (custom_s);
	} while (*custom_s++ != '\0');

	return (NULL);
}

