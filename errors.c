#include "shell.h"

/**
 *_eputs - It Prints an input string
 * @str: String to be printed
 *
 * Return: return nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes the Character c a to stderr
 * @c: Character to print
 *
 * Return: on success return 1.
 * on error, a -1 is returned, and an errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Writes the Character c to a given fd
 * @c: Character to print
 * @fd: a filedescriptor to write into
 *
 * Return: on success 1 is returned.
 * on error, a -1 is returned, and an errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - IT Prints the input string
 * @str: String to be printed
 * @fd: a filedescriptor to write into
 *
 * Return: Number of the chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
