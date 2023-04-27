#include "KIMBA.H"

/**
 * string_length - function that returns the length of a string
 * @s: variable that contains the string whose length to check
 *
 * Return: integer length of string
 */
int string_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * str_cmp - function that performs comparison of two strings.
 * @s1:variable with the first strang
 * @s2: variable with the second strang
 *
 * Return:if s1 < s2 neg, if s1 > s2 pos, if s1 == s2 zero
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with -function that checks if needle starts with haystack
 * @haystack:variable with string to search
 * @needle: the substring to find
 *
 * Return: either returns address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str_cat - function that concatenates two strings
 * @destination: variable with the destination buffer
 * @destination: variable with the destination buffer
 * @src:variable with the source buffer
 *
 * Return: returns pointer to destination buffer
 */
char *str_cat(char *destination, char *src)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*src)
		*destination++ = *src++;
	*destination = *src;
	return (ret);
}
