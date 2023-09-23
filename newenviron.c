#include "shell.h"

/**
 * _getenv - Get the value of a variable in the environment.
 * @info: A pointer to a structure that contains prospective arguments.
 * @name: The variable's name in the environment.
 *
 * Return: If an environment variable is detected, it returns
 * its value; otherwise, it returns NULL.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p); /* Return the environment variable's value. */
		node = node->next;
	}
	return (NULL); /* If the enviro var could not be discovered, return NULL. */
}

/**
 * _myunsetenv - Delete an environment variable.
 * @info: A pointer to a structure that contains prospective arguments.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * _mysetenv - Create a new environment variable or change an existing one.
 * @info: A pointer to a structure that contains prospective arguments.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * populate_env_list - Fill out the environment related list.
 * @info: A pointer to a structure that contains prospective arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	/* Fill the linked list with environment variables. */
	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node; /* Refresh the environment variable linked list */
	return (0);
}

/**
 * _myenv - Check to see if an exit argument is provided.
 * @info: A pointer to a structure that contains prospective arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	/* Use this function to print the environment variables. */
	print_list_str(info->env);
	return (0);
}
