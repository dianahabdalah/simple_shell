#include "shell.h"

/**
 * get_environment - Returns a copy of the environment strings as an array
 * @info: Structure containing potential arguments (not used here)
 * Return: Array of environment strings
 */
char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments (not used here)
 * @variable: The environment variable to remove
 * Return: 1 if deleted, 0 otherwise
 */
int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *ptr;

	if (!node || !variable)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, variable);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * set_environ_var - Initialize new environ var or modify an existing one
 * @info: Structure containing potential arguments (not used here)
 * @variable: The environment variable name
 * @value: The environment variable value
 * Return: Always 0
 */
int set_environ_var(info_t *info, char *variable, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!variable || !value)
		return (0);

	buf = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, variable);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, variable);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

