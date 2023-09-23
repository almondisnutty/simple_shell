#include "shell.h"

/**
 * interactive - To make sure the shell is running and in interactive mode.
 * @info: Pointer to info structure.
 *
 * Return: 1 if the mode is interactive; 0 if otherwise.
 */
int interactive(info_t *info)
{
	/* Verify that readfd is within the permitted range that STDIN is terminal.*/
	return (isatty(STDIN_FILENO) && info->readfd <= MAX_ALLOWED_FD);
}

/**
 * is_delim - Verifies if character is a delimiter.
 * @c: The character being verified.
 * @delim: The delimiter string.
 *
 * Return: If the character is a delimiter, it returns 1, else it returns 0.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _atoi - A string is changed into an integer.
 * @s: The string that will be changed.
 *
 * Return: 0 if there are nil numbers present string,
 * if otherwise return the converted number.
 */
int _atoi(char *s)
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

/**
 * _isalpha - Determines if a character is an alphabetic character.
 * @c: The character to be examined.
 *
 * Return:If c is an alphabetic character, 1 is returned; otherwise, 0
 */
int _isalpha(int c)
{
	/* If c is an alpha character, a value of 1 is returned; else, a value of 0*/
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
