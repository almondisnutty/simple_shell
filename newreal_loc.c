#include "shell.h"

/**
 * _realloc - Adjusts the size of a memory block.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: Previous size in bytes of the block.
 * @new_size: New size in bytes for the block.
 *
 * Return: Pointer to the reallocated block of memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size)); /* If ptr is NULL, just provide new memory */

	if (!new_size)
		return (free(ptr), NULL); /*If new_size is 0, clear memory and return NULL*/

	if (new_size == old_size)
		return (ptr); /*If new_size equals old_size, no reallocation is needed*/

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size]; /*Transfer contents from old to new*/

	free(ptr); /* Create space the old memory */
	return (p); /* Return pointer to the new reallocated memory */
}

/**
 * ffree - Releases memory allocated for a string of strings.
 * @pp: String of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a); /*Releases memory allocated for a str of strs (arr of pointers)*/
}

/**
 * _memset - Populates memory with a specific byte.
 * @s: The pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: Number of bytes to be filled.
 * Return: (s) A pointer to memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s); /* Populate memory with the specified byte value */
}
