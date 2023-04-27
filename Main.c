#include "KIMBA.H"

/**
 * main - this is the entry point
 * @ac: the arg count
 * @av: the arg vector
 *
 * Return: 0 upon success, 1 upon error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs_(av[0]);
				_eputs_(": 0: Can't open ");
				_eputs_(av[1]);
				_e_putchar('\n');
				_e_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_envlist(info);
	read_hist(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
