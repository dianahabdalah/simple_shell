#include "shell.h"

/**
 * my_eputs - display a string to standard error
 * @str: the string to display
 *
 * Return: Nothing
 */
void my_eputs(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		my_eputchar(str[index]);
		index++;
	}
}

/**
 * my_eputchar - write a character to stderr
 * @c: The character to write
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set accordingly.
 */
int my_eputchar(char c)
{
	static int buf_index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || buf_index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, buf_index);
		buf_index = 0;
	}

	if (c != FLUSH_BUFFER)
		buffer[buf_index++] = c;

	return (1);
}

/**
 * my_putfd - write a character to a given file descriptor
 * @c: The character to write
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set accordingly.
 */
int my_putfd(char c, int fd)
{
	static int buf_index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || buf_index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, buf_index);
		buf_index = 0;
	}

	if (c != FLUSH_BUFFER)
		buffer[buf_index++] = c;

	return (1);
}

/**
 * my_putsfd - display a string to a given file descriptor
 * @str: the string to display
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int my_putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		char_count += my_putfd(*str++, fd);
	}

	return (char_count);
}

