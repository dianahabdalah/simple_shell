#include "shell.h"

/**
 * input_buf - the Buffers chained commands
 * @info: the Param struct
 * @buf: the Address of buffer
 * @len: the Address of the len var
 *
 * Return: it returns bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing is left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* resposnible for removing trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is it a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - it gets line minus a newline
 * @info: RETURNS the param  struct
 *
 * Return: it returns bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' Command of chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* There is  commands left in the chain buffer */
	{
		j = i; /* the Init new iterator to THE current buf position */
		p = buf + i; /* it gets the  pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* IT Iterate to the semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* teh Increment past the nulled ';'' */
		if (i >= len) /* it has Reached end of buffer? */
		{
			i = len = 0; /* Resets the position and the length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* it pass back the pointer to the current command position */
		return (_strlen(p)); /* it Return length of the current command */
	}

	*buf_p = buf; /* or else not chain, pass the back buffer from _getline() */
	return (r); /*Returns the  length of the buffer from _getline() */
}

/**
 * read_buf - it is responsible for  reading  a buffer
 * @info: the parameter struct
 * @buf: The Buffer
 * @i: The Size
 *
 * Return: always return r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - it gets next line of input from the STDIN
 * @info: the parameter struct
 * @ptr: The Address of the pointer to the buff, preallocated or NULL
 * @length: the size of the preallocated ptr buffer if not NULL
 *
 * Return: always return an s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* maLLOC faILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - The Blocks ctrl-C
 * @sig_num: Signal num
 *
 * Return: always return Void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
