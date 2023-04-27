#include "KIMBA.H"

/**
 * input_buf - This buffers all chained commands
 * @info: the parameter struct
 * @buf: the buffer address
 * @len: the len var address
 *
 * Return: the bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/*b_free((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(_sigint, _sigintHandler);
#if USEget_line
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_hist_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _getinput - this gets a line minus the newline
 * @info: this is a parameter struct
 *
 * Return: the bytes read
 */
ssize_t _getinput(info_t *info)
{
	static char *buf; /* this is the ';' command for chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* End Of Funct */
		return (-1);
	if (len) /* commands on the left of the chain buffer */
	{
		j = i; /* init new iterator to the current buf position */
		p = buf + i; /* ps get pointer for return */

		chain_check(info, buf, &j, i, len);
		while (j < len) /* iterate to ':' or end */
		{
			if (_ischain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled smicolon */
		if (i >= len) /* did we reach end of buffer? wk */
		{
			i = len = 0; /* resets position and the length */
			info->cmd_buffer_type = CMD_NORM;
		}

		*buf_p = p; /* nb this will pass back pointer to current command position */
		return (string_len(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from get_line() */
	return (r); /* returns length of buffer from get_line() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
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
 * get_line - this gets the next line of input from STDIN
 * @info: the parameter of struct
 * @ptr: the address of a pointer to buffer, preallocated or NULL
 * @length: this is size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
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

	c = string_char(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		string_cat(new_p, buf + i, k - i);
	else
		string_cpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _sigintHandler - this blocks ctrl-C
 * @sig_num: is signal number
 *
 * Return: a void
 */
void _sigintHandler(__attribute__((unused))int sig_num)
{
	puts_("\n");
	puts_("$ ");
	_putchar(BUF_FLUSH);
}
