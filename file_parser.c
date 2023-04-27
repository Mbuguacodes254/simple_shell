#include "KIMBA.H"

/**
 * is_command - this function determines if a file is an executable command
 * @info: variable shows the info structure
 * @path:indicates the path to the file
 *
 * Return: if true 1, else 0
 */
int is_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - function copies characters
 * @pathstr:variable that shows the PATH string
 * @start: it is the starting index variable
 * @stop:this is the stopping index variable
 *
 * Return: pointer to a new buffer
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * _findpath - function that finds this command in the PATH string
 * @info: variable for the info struct
 * @pathstr: this is the the PATH string variable
 * @cmd: the command to find variable
 *
 * Return: returns full path of cmd if found or NULL
 */
char *_findpath(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_length(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
