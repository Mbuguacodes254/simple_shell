#include "KIMBA.H"

/**
 * my_env - This prints the current environment
 * @info: variable contains potential argument that are used in maintaining the
 *          constant function prototypes.
 * Return: it is Always 0
 */
int my_env(info_t *info)
{
	_printlist_str(info->env);
	return (0);
}

/**
 * get_env - this prototype gets the value of an environment variable
 * @info: variable that contains potential arguments that are used to maintain
 * @name: environment variable name
 *
 * Return: it returns the value
 */
char *get_env(info_t *info, const char *name)
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
 * myset_env - this prototype Initializes a new environment variable
 *             or it modifies an existing variable
 * @info:variabel contains potential arguments that are used to maintain
 *        constant function prototypes.
 *  Return: Always 0
 */
int myset_env(info_t *info)
{
	if (info->argc != 3)
	{
		_e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunset_env - this prototype Removes an environment variable
 * @info: variable that contains potential arguments that are used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int myunset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_e_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_envlist -this populates env linked list
 * @info: variable that containins potential arguments that maintain
 * constant variable prototyps.
 * Return: Always 0
 */
int populate_envlist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
