#include "shell.h"

/**
 * _myenv - Prints current environment
 * @info: structure having potential arguments. used to maintain a
 *          constant function prototype.
 * Return: always returns 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - fetches the value of an environ variable
 * @info: structure having potential arguments. used to maintain a
 * @name: an env var name
 *
 * Return: returns a value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - it initialize new environment variable,
 *             or modify existing one
 * @info: structure having potential arguments. used to maintain a
 *        constant prototype function.
 *  Return: always returns 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - used to remove environment variable
 * @info: structure having potential arguments. used to maintain a
 *        constant prototype function.
 *  Return: always returns0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - It Populates env linked list
 * @info: Structure having potential arguments. used to maintain a
 *          constant prototype function.
 * Return: always returns 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
