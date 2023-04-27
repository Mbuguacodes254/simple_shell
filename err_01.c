#include "KIMBA.H"

/**
 * err_atoi - This converts string to number
 * @s: string to be converted
 * Return: 0 if no numbers in string, otherwise return converted number
 *       -1 upon error
 */
int err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * prt_err - prints the error message
 * * @info: return info struct and parameter
 * @estr: the string with specific error type
 * Return: 0 if no numbers in string, otherwise the converted number
 *        -1 upon error
 */
void prt_err(info_t *info, char *estr)
{
	eputs_(info->fname);
	eputs_(": ");
	prt_d(info->line_count, STDERR_FILENO);
	eputs_(": ");
	eputs_(info->argv[0]);
	eputs_(": ");
	eputs_(estr);
}

/**
 * prt_d - this is a function printing a decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor to write to
 *
 * Return: number of ptrinted characters
 */
int prt_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _e_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - the converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: the argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - a function replacing first instance of '#' with '\0'
 * @buf: the address of the string to be modified
 *
 * Return: 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
