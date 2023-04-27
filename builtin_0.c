#include "KIMBA.H"

/**
 * my_exit - this exits the shell
 * @info: variable that contains potential arguments it is used to maintain
 * the constant function prototypes.
 * Return:this function exits with an exit status that is given
 * (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int check_exit;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		check_exit = err_attoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			prt_err(info, "Illegal number: ");
			e_puts(info->argv[1]);
			e_putchar('\n');
			return (1);
		}
		info->err_num = err_attoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes process current directory
 * @info:variable  that contains potential arguments it is used to maintain
 * constant function prototypes.
 * Return:it Always returns 0
 */
int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_return;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_return = /* TODO: what should this be? */
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_return = /* TODO: what should this be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
	if (chdir_return == -1)
	{
		prt_err(info, "can't cd to ");
		e_puts(info->argv[1]), e_putchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - this func changes the current directory of the processes
 * @info: variable contains potential arguments that are used to maintain
 * constant function prototypes.
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

