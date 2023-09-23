#include "shell.h"

/**
 * _strncat - Concatenates two strings with a defined maximum length.
 * @dest: The string where the content is  appended, which is the destination.
 * @src: The string from which content is being appended, acting as the source.
 * @n: The amount of characters that must be copied.
 *
 * Return: The target string's pointer.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	/* Determine the termination point of the destination string */
	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	/* Add characters from the src to the dest up to maximum of 'n' characters. */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	/*Make sure that the destination string is terminated with a null char */
	if (j < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strncpy - Copies a string of a certain length.
 * @dest: The location string to be stored in.
 * @src: The original string.
 * @n: The amount of characters that must be copied.
 *
 * Return: The target string's pointer.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	/* Copy up to n characters from src to dest */
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	/*Ensure the remaining characters in 'dest' are filled with the null char*/
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strchr - Finds the initial instance of a specific char within a str.
 * @s: The string to be examined.
 * @c:  The character to look for.
 *
 * Return: A pointer to the first instance of the character in the string.
 * Supposing character is not located, it returns NULL.
 */
char *_strchr(char *s, char c)
{
	/* Find character 'c' in string 's'. */
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL); /* Character could not be found */
}
