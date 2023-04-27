#include "KIMBA.H"

/**
 * interactive - returns true if the shell is in  interactivemode
 * @info: struct address
 *
 * Return: 1 if in  interactivemode, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isdelim - checks if character marks the beginning or end of a unit of data
 * @c: the character to check
 * @delim: delimeter string
 * Return: 1 if true, if false 0
 */
int isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - checks alphabet character
 * @c: Character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * atoi - converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
