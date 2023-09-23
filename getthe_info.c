#include "shell.h"

/**
 * clear_info - Initialize an info_t structure with NULL values in its fields.
 * @info: Pointer to the info_t structure for clearing.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes an info_t struct with given arguments.
 * @info: Pointer to the info_t structure to be initialized.
 * @av: Argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Releases the memory allocated for fields of an info_t structure.
 * @info: Pointer to the info_t structure for memory deallocation.
 * @all:  Flag indicating whether to free all fields or not.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv); /* Deallocate the argv array. */
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg); /* Deallocate the command argument string. */
		if (info->env)
			free_list(&(info->env)); /*  Deallocate the environment linked list. */
		if (info->history)
			free_list(&(info->history)); /* Deallocate the history linked list. */
		if (info->alias)
			free_list(&(info->alias)); /* Deallocate the alias linked list. */
		ffree(info->environ); /* Deallocate the environment strings array. */
		info->environ = NULL;
		bfree((void **)info->cmd_buf); /* Deallocate the command buffer. */
		if (info->readfd > 2)
			close(info->readfd); /* Close the read file handle. */
		_putchar(BUF_FLUSH); /* Empty the output buffer. */
	}
}
