#include "KIMBA.H"

/**
 * get_hist_file -this is a document that gets the history file
 * @info: function parameter structure
 *
 * Return: allocated string that contains the history file
 */

char *get_hist_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char)
	* (string_length(dir) + string_length(HIST_FILE) + 2));
	*if (!buf)
		return (NULL);
	buf[0] = 0;
	str_copy(buf, dir);
	str_cat(buf, "/");
	str_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist -prototype allows creating a file, or appends to an existing file
 * @info: this is the parameter structure
 *
 * Return: on success 1, otherwise -1
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - prototype allows for reading history from a file
 * @info: the parameter structure
 *
 * Return: on success returns histcount, else 0
 */
int read_hist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renum_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - this prototype adds entry to a history linked list
 * @info:variable containing potential arguments they are used to maintain
 * @buf: buffer
 * @linecount: this is a func that gives the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
