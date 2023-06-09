#include "KIMBA.H"

/**
 * my_hist - shows history list, one command by line, preceded
 *              with line numbers, from 0.
 * @info: a structure containing the potential arguments used to maintain
 *        constant function prototype.
 *  Return: 0
 */
int my_hist(info_t *info)
{
	_printlist(info->history);
	return (0);
}

/**
 * _unsetalias - sets an alias to string
 * @info: parameter struct
 * @str: string alias
 *
 * Return: Always 0 upon success, 1 upon error
 */
int _unsetalias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = string_char(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_index_node(info->alias, node_startswith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _setalias - it sets alias to a string
 * @info: parameter struct
 * @str: string alias
 *
 * Return: Always 0 upon success, 1 upon error
 */
int _setalias(info_t *info, char *str)
{
	char *p;

	p = string_char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unsetalias(info, str));

	_unsetalias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _printalias - prints alias string
 * @node: alias node
 *
 * Return: Always 0 upon success, 1 upon error
 */
int _printalias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = string_char(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		puts_(p + 1);
		puts_("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @info: The structure containing potential arguments used to maintain
 *          constant function prototype.
 * Return: 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = string_char(info->argv[i], '=');
		if (p)
			_setalias(info, info->argv[i]);
		else
			_printalias(node_startswith(info->alias, info->argv[i], '='));
	}

	return (0);
}
