#include "shell.h"

/**
 * convert_string_to_integer_err - Function converts String to an integer.
 * @s: The input string to be converted.
 *
 * Return: The converted integer if successful, or -1 on error.
 */
int convert_string_to_integer_err(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* Ignore leading '+' character, if any */
	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1); /* Invalid character encountered */
	}
	return (result);
}

/**
 * print_error_message - This function prints an error message.
 * @info: The parameter and return info struct.
 * @estr: String containing the specified error type.
 *
 * Return: None.
 */
void print_error_message(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_decimal - This function prints a decimal (integer) number (base 10).
 * @input: The input integer.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		output_char = _eputchar; /* Use error output function */
	if (input < 0)
	{
		abs_value = -input;
		output_char('-');
		count++;
	}
	else
		abs_value = input;
	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			output_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	output_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - This function is a converter, similar to itoa.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *char_array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	char_array = flags CONVERT_LOWERCASE "0123456789abcdef"; : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = char_array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_hashtag -  Function replaces first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_first_hashtag(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

