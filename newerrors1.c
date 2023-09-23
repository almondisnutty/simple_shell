#include "shell.h"

/**
 * _eputs - This function outputs an input str to the standard error (stderr).
 * @str: The string to be printed.
 *
 * Return: Null
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	/* Each character in the string is printed to stderr. */
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _putfd - The character c is written to the specified file descriptor..
 * @c: The character that will be printed.
 * @fd: The file descriptor to which to write.
 *
 * Return: In case of success, 1 is returned; in case of failure, -1 is
 * given, and errno is set approximately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	/* flush the buffer if the character is BUF_FLUSH or the buffer is full. */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i); /* Save the buffer to the specified file descriptor. */
		i = 0;
	}

	/* If the buffer is not BUF_FLUSH, add the character to it. */
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _eputchar -The character c is written to the standard error stream..
 * @c: The character that will be printed.
 *
 * Return: In case of success, 1 is returned; in case of failure,
 * -1 is given, and errno is set approximately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	/* flush the buffer if the character is BUF_FLUSH or the buffer is full. */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i); /* To stderr, write the buffer */
		i = 0;
	}

	/* If the buffer is not BUF_FLUSH, add the character to it. */
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfd - Prints the provided file descriptor's input string.
 * @str: The string to be printed.
 * @fd: The file descriptor to which to write.
 *
 * Return: The volume of characters input.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	/* Each character of the str is printed to the specified file descriptor*/
	while (*str)
	{
		i += _putfd(*str++, fd);
	}

	return (i);
}

