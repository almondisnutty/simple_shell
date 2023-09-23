#include "shell.h"
int unset_alias(info_t *info, char *str);

/**
 * set_alias - In the list, add or amend an alias.
 * @info: The argument struct's pointer.
 * @str: The string that represents the alias.
 *
 * Return: 0 for success, 1 for failure
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str)); /* If value is nil, delete alias */

	unset_alias(info, str); /* delete  alias if it the alias is already present*/
	return (add_node_end(&(info->alias), str, 0) == NULL); /* Add alias to list*/
}

/**
 * unset_alias - Take an alias out of the list.
 * @info: The argument struct's pointer.
 * @str: The string that represents the alias.
 *
 * Return: 0 for success, 1 for failure
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * print_alias - output an alias str.
 * @node: Points to alias node.
 *
 * Return:0 for success, 1 for failure
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '='); /* Look for the equal symbol in the string. */
		for (a = node->str; a <= p; a++)
			_putchar(*a); /* Print alias name */
		_putchar('\'');
		_puts(p + 1); /* Print alias value */
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myexit - Exit the shell
 * @info: A reference to a structure containing potential arguments.
 * This pointer is used to keep function prototypes consistent.
 * Return: Exit status: 0 if info->argv[0] is true, if false "exit"
 */
int _myexit(info_t *info)
{
	int exit_check;

	/* Examine whether an exit argument is provided. */
	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2); /* Return exit status */
	}
	info->err_num = -1;
	return (-2); /* Return exit status */
}

/**
 * _myalias - Replicate the alias built-in command.
 * @info: A reference to a structure containing potential arguments.
 * This command is used to manage alias commands.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node); /* Print aliases to stdout */
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '='); /* Look for equal symbol in the str*/
		if (p)
			set_alias(info, info->argv[i]); /* update alias */
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

