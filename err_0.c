#include "KIMBA.H"

/**
 * e_puts - this a prototype that usually prints an input string
 * @str:this is the string that is to be printed
 *
 * Return: returns Nothing
 */
void e_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		e_putchar(str[i]);
		i++;
	}
}

/**
 * e_putchar -the prototype writes the character c to stderr prototype
 * @c: this shows The character to print
 *
 * Return: On success return 1.
 * On error it returns -1 is and errno is set appropriately.
 */
int e_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_fd -this prototype usually writes the character c to given fd
 * @c: this is the character to print
 * @fd: this is The filedescriptor to write to
 *
 * Return: 1 indicated success.
 * -1 is returned on error, and errno is set appropriately.
 */
int put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * puts_fd - this prototype prints out an input string
 * @str:this is the string to be printed
 * @fd: this is the filedescriptor to write to
 *
 * Return: it should return the number of characters put
 */
int puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_fd(*str++, fd);
	}
	return (i);
}
