#include "KIMBA.H"

/**
 * str_copy - function that copies a string
 * @destination: the destination variable
 * @src: variable with the source
 * Return: pointer to destination is returned
 */
char *str_copy(char *destination, char *src)
{
	int i = 0;

	if (destination == src || src == 0)
		return (destination);
	while (src[i])
	{
		destination[i] = src[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

/**
 * str_duplicate - function that duplicates a string
 * @str:variable with the string to duplicate
 * Return: pointer to the duplicated string is returned
 */
char *str_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - function that prints an input string
 * @str:variable with the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar -function that writes the character c to stdout
 * @c: variable with The character to print
 *
 * Return:succesful 1.
 * unsuccesful -1 is returned, and error number is set accordingly.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
