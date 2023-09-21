#include "shell.h"

/**
 * check_shell_mode - Check if the shell is running in interactive mode.
 * @shell_info: A pointer to a struct containing shell information.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int check_shell_mode(info_t *shell_info)
{
	return (isatt(STDIN_FILENO) && shell_info->read_descriptor <= 2);
}

/**
 * is_separator_char - Check if a character is a separator.
 * @character: The character to check.
 * @separator_set: The set of separator characters.
 *
 * Return: 1 if the character is a separator, 0 if not.
 */
int is_separator_char(char character, char *separator_set)
{
	while (*separator_set)
		if (*separator_set++ == character)
			return (1);
	return (0);
}

/**
 * is_alphabetic_char - Determine if a character is alphabetic.
 * @ch: The character to check.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int is_alphabetic_char(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * custom_string_to_int - Convert a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in the string, Converted number otherwise.
 */
int custom_string_to_int(char *str)
{
	int i, sign = 1, flag = 0, result;
	unsigned int integer_result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			integer_result *= 10;
			integer_result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -integer_result;
	else
		result = integer_result;

	return (result);
}

