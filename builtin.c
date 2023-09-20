#include "shell.h"

/**
 * custom_exit - Terminate the shell.
 * @info: Structure holding potential arguments.
 *
 * Return: Exits the shell with a specified exit status (0) if info->argv[0]
 * is not "exit".
 */
int custom_exit(info_t *info)
{
	int exit_value;

	if (info->argv[1]) /* Check for an exit argument */
	{
		exit_value = _custom_atoi(info->argv[1]);
		if (exit_value == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _custom_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * custom_cd - Change the working directory of the process.
 * @info: Structure holding potential arguments.
 *
 * Return: Always returns 0.
 */
int custom_cd(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: Handle getcwd failure message here\n");
	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_result =
				chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result =
			chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_error(info, "Unable to change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_help - Display a help message.
 * @info: Structure holding potential arguments.
 *
 * Return: Always returns 0.
 */
int custom_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("The 'help' function operational,help message not implemented.\n");
	if (0)
		_puts(*arg_array); /* Temporary workaround for unused variable warning */
	return (0);
}

