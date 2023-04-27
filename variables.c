#include "KIMBA.H"

/**
 * _ischain -func to test current char in buffer is a chain delimeter
 * @info: variable with the parameter struct
 * @buf: variable with the char buffer
 * @p: variable with address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _ischain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_AND;
	}

	else if (buf[j] == ';') /
	{
		buf[j] = 0;
		info->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chain_check - func checks we should continue chaining based on last status
 * @info: variable with the parameter structures
 * @buf: variable with the char buffer
 * @p: variable with address of current position in buffer
 * @i: variable with the starting position in buffer
 * @len: variable withlength of buffer
 *
 * Return: Void
 */
void chain_check(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * rep_alias - replaces an aliases in the tokenized string
 * @info: variable with the parameter struct
 * Return: replaced 1, else 0
 */
int rep_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_startswith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = string_char(node->str, '=');
		if (!p)
			return (0);
		p = str_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * rep_variables - function that replaces vars in the tokenized string
 * @info:variable with the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_cmp(info->argv[i], "$?"))
		{
			rep_strng(&(info->argv[i]),
					str_duplicate(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			rep_strng(&(info->argv[i]),
					str_duplicate(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_startswith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rep_strng(&(info->argv[i]),
					str_duplicate(string_char(node->str, '=') + 1));
			continue;
		}
		rep_strng(&info->argv[i], str_duplicate(""));

	}
	return (0);
}

/**
 * rep_strng - function that replaces string
 * @old:variable with address of old string
 * @new: variable with new string
 *
 * Return: replaced 1, else 0
 */
int rep_strng(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
