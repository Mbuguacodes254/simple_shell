#include "KIMBA.H"

/**
 * get_env - function that returns the string array copy of our environment
 * @info: variable containing potential argument that are used to maintain
 *          constant prototype functions.
 * Return: it will Always return 0
 */
char **get_env(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strg(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environ - the prototype allows to Remove an environment variable
 * @info: variable containing potential arguments that are used to maintain
 *        constant prototype functions.
 *  Return: after deleting 1, else 0
 * @var: the string env var property
 */
int unset_environ(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env - this prototype allows Initializing a new environment variable,
 *             or modifying an existing one
 * @info:variable containsing potential arguments that are Used to maintain
 *        constant prototype functions.
 * @var: the variable of the string env var property
 * @value: the string envvironment variable value
 *  Return: this Always returns 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(string_length(var) + string_length(value) + 2);
	if (!buf)
		return (1);
	str_copy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
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
