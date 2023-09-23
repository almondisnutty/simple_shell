#include "shell.h"

/**
 * bfree - Frees a pointer and assigns it a value of NULL.
 * @ptr: Address of the pointer to be freed.
 *
 * Return: 1 if successfully freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr) /* Verify if the pointer and its value are valid. */
	{
		free(*ptr); /* Release the memory pointed to by the pointer. */
		*ptr = NULL; /* Assign NULL to the pointer. */
		return (1); /* Mark that memory has been freed. */
	}
	return (0); /* Mark that no memory has been freed. */
}
