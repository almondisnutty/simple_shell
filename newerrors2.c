#include "shell.h"

/**
 * remove_comments - Replaces earliest occurence of '#' with '\0'.
 * @buf: location of the string in memory to modify.
 *
 * Return: Null.
 */
void remove_comments(char *buf)
{
	int i;

	/* Replaces earliest occurence of '#' with '\0'. */
	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * print_d - Prints decimal.
 * @input: The input number that will be printed.
 * @fd: File descriptor to be written to.
 *
 * Return: The volume of char printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	/* considering if standard output or standard error would be appropriate */
	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	/* Takes care of values less than 0 */
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	/* Print every digit */
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
 * print_error - This function prints an error message to the stderr.
 * @info: The struct for parameter and return information.
 * @estr: String holding the error type specified.
 *
 * Return: Null
 */
void print_error(info_t *info, char *estr)
{
	/* details: Number of line, command name, error type and filename */
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * convert_number - Converts an int to a str representation.
 * @num: The int to be converted to a str.
 * @base: The base the nuber will be converted to.
 * @flags: Indicates conversion alternatives.
 *
 * Return: The str representation of the int.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	/* Takes care of values lesss than 0 if necessary */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	/* Determine the character array for the specified base. */
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	/* Convert the numeric value to a decimal representation. */
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * _erratoi - This function converts a string to an integer.
 * @s: The string to be converted to an integer.
 *
 * Return: If successful return the converted number else return -1.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	/* negate '+' sign when present */
	if (*s == '+')
		s++;

	/* Convert str to int */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			/* Test for overflow of int */
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1); /* Character encountered was invalid */
	}

	return (result);
}
