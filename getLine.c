#include "shell.h"

/**
 * custom_input_buffer - Buffer chained commands
 * @param_info: parameter struct
 * @param_buf: address of buffer
 * @param_len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(param_info_t*param_info,char**param_buf, size_t*param_len)
{
	ssize_t result = 0;
	size_t len_p = 0;

	if (!*param_len) /* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)param_info->cmd_buffer);*/
		free(*param_buf);
		*param_buf = NULL;
		signal(SIGINT, custom_sigint_handler);
#if USE_GETLINE
		result = getline(param_buf, &len_p, stdin);
#else
		result = custom_getline(param_info, param_buf, &len_p);
#endif
		if (result > 0)
		{
			if ((*param_buf)[result - 1] == '\n')
			{
				(*param_buf)[result - 1] = '\0'; /* Remove trailing newline */
				result--;
			}
			param_info->line_count_flag = 1;
			custom_remove_comments(*param_buf);
			custom_build_histo_list(param_info,*param_buf,param_info->histo_count++);
			/* if (custom_strchr(*param_buf, ';')) Is this a command chain? */
			{
				*param_len = result;
				param_info->cmd_buffer = param_buf;
			}
		}
	}
	return (result);
}

/**
 * custom_get_input - Get a line minus the newline
 * @param_info: parameter struct
 *
 * Return: bytes read
 */
ssize_t custom_get_input(param_info_t *param_info)
{
	static char *param_buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t result = 0;
	char **buf_p = &(param_info->arg), *p;

	custom_putchar(BUF_FLUSH);
	result = custom_input_buffer(param_info, &param_buf, &len);
	if (result == -1) /* EOF */
		return (-1);
	if (len) /* We have commands left in the chain buffer */
	{
		j = i; /* Initialize new iterator to current buf position */
		p = param_buf + i; /* Get pointer for return */

		custom_check_chain(param_info, param_buf, &j, i, len);
		while (j < len) /* Iterate to semicolon or end */
		{
			if (custom_is_chain(param_info, param_buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';' */
		if (i >= len) /* Reached end of buffer? */
		{
			i = len = 0; /* Reset position and length */
			param_info->cmd_buffer_type = CMD_NORMAL;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (custom_strlen(p)); /* Return length of current command */
	}

	*buf_p = param_buf; /* Not a chain, pass back buffer from custom_getline() */
	return (result); /* Return length of buffer from custom_getline() */
}

/**
 * custom_read_buffer - Read a buffer
 * @param_info: parameter struct
 * @param_buf: buffer
 * @param_i: size
 *
 * Return: result
 */
ssize_t read_buffer(param_info_t*param_info,char*param_buf,size_t*param_i)
{
	ssize_t result = 0;

	if (*param_i)
		return (0);
	result = read(param_info->readfd, param_buf, READ_BUFFER_SIZE);
	if (result >= 0)
		*param_i = result;
	return (result);
}

/**
 * custom_getline - Get the next line of input from STDIN
 * @param_info: parameter struct
 * @param_ptr: address of pointer to buffer, preallocated or NULL
 * @param_length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int custom_getline(param_info_t*param_info,char**param_ptr,size_t*param_length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t result = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *param_ptr;
	if (p && param_length)
		s = *param_length;
	if (i == len)
		i = len = 0;

	result = custom_read_buffer(param_info, buffer, &len);
	if (result == -1 || (result == 0 && len == 0))
		return (-1);

	c = custom_strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = custom_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		custom_strncat(new_p, buffer + i, k - i);
	else
		custom_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (param_length)
		*param_length = s;
	*param_ptr = p;
	return (s);
}

/**
 * custom_sigint_handler - Blocks Ctrl-C
 * @sig_num: The signal number
 *
 * Return: void
 */
void custom_sigint_handler(__attribute__((unused)) int sig_num)
{
	custom_puts("\n");
	custom_puts("$ ");
	custom_putchar(BUF_FLUSH);
}

