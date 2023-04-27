#include "KIMBA.H"

/**
 **string_cpy - this is a prototype that copies a string
 *@destination: variable destination of the string it should be to be copied to
 *@src: the func shows the source string
 *@n: this is the amount of characters that are to be copied
 *Return: it should return a the concatenated string
 */
char *string_cpy(char *destination, char *src, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		destination[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **string_cat - this is character concatenates two strings
 *@destination:the destination is the first string
 *@src: the source is the second string
 *@n: this func is the amount of bytes to be used maximally
 *Return: it should return a concatenated string
 */
char *string_cat(char *destination, char *src, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destinationination[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		destinationination[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 **string_char - the prototype is supposed to locate a character in a string
 *@s: this func indicates the string to be parsed
 *@c: this func shows the character to look for
 *Return: returns (s) as a pointer to the memory area s
 */
char *string_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
