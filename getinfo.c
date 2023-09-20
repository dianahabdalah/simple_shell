#include "shell.h"

/**
 * initialize_info - Initializes the info_t struct
 * @info: Pointer to the info_t struct
 */
void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * configure_info - Configures the info_t struct
 * @info: Pointer to the info_t struct
 * @av: Argument vector
 */
void configure_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = tokenize_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicate_string(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_aliases(info);
		replace_variables(info);
	}
}

/**
 * release_info - Releases memory associated with the info_t struct fields
 * @info: Pointer to the info_t struct
 * @free_all: True if freeing all fields
 */
void release_info(info_t *info, int free_all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (free_all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_linked_list(&(info->env));
		if (info->history)
			free_linked_list(&(info->history));
		if (info->alias)
			free_linked_list(&(info->alias));
		free_string_array(info->environ);
		info->environ = NULL;
		free_buffer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(FLUSH_BUFFER);
	}
}

