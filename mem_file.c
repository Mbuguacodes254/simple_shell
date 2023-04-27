#include "KIMBA.H"

/**
 * b_free -Function that frees a pointer and NULLs the address
 * @ptr: it points address of the pointer to free
 *
 * Return: if freed 1, else0.
 */
int b_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
