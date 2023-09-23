#include "shell.h"

/**
 * hsh - Main shell loop
 * @info: The info parameter
 * which contains shell-related information
 * is both an input and output parameter for this function.
 * @av: The argument vector from main()
 *
 * This function implements the main loop of the shell.
 * It repeatedly reads user input, processes commands,
 * and executes them until the user exits
 * or an error occurs.
 * Return: 0 on success, 1 on error or an error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ "); /* Show shell prompt */
		_eputchar(BUF_FLUSH);
		r = get_input(info); /* Read user entry */
		if (r != -1)
		{
			set_info(info, av); /* Ready command info */
			builtin_ret = find_builtin(info); /* Checks if the cmd is a built-in cmd */
			if (builtin_ret == -1)
				find_cmd(info); /* If cmd is not a built-in find and execute the cmd */
		}
		else if (interactive(info))
			_putchar('\n'); /* Print newline if there is no input */
		free_info(info, 0); /* Temporarily free info fields */
	}
	write_history(info); /* Save history */
	free_info(info, 1); /* Free every info field */
	if (!interactive(info) && info->status)
		exit(info->status); /* Exit using the command's exit status */
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num); /* Exit using error number if needed */
	}
	return (builtin_ret);
}

/**
 * find_cmd - This searches for and executes a command located in the PATH.
 * @info: This contains shell-related information
 * and is both an input and output parameter for this function.
 * This function searches for the specified command in the directories listed
 * in the PATH environment variable. If the command is found,
 * it executes it with the given arguments.
 * If the command is not found, it prints an error message.
 */
void find_cmd(info_t *info)
{
	char *path = NULL; /* This function stores the path to the executable. */
	int i, k; /* Loop counters */

	info->path = info->argv[0]; /* Boots the path variable with cmd name. */
	if (info->linecount_flag == 1)
	{
		info->line_count++; /* Increase line_count if linecount_flag is set */
		info->linecount_flag = 0; /* Reset linecount_flag */
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++; /* Count the characters that are not delimiters. */
	if (!k)
		return; /* If there are no non-delimiter characters, return. */

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info); /* Run the command */
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info); /* If it's a built-in command execute it. */
		else if (*(info->arg) != '\n')
		{
			info->status = 127; /* If cmd absent, exit status indicate this */
			print_error(info, "not found\n"); /* Prints error message */
		}
	}
}

/**
 * find_builtin - Locates a builtin command
 * @info: The info parameter, which contains shell-related information
 * is both an input and output parameter for this function.
 * This function looks for a built-in command within the arguments
 * provided in the info struct.
 * If a match is found,
 * it proceeds to execute the associated built-in function.
 * Return: -1 if builtin can not be located,
 *         0 if builtin executed successfully,
 *         1 if builtin can be located but not successful,
 *         2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret); /* Returns the value built-in command execution */
}

/**
 * fork_cmd - Forks a child process to execute the command.
 * @info: The info parameter, which contains shell-related information
 * is both an input and output parameter for this function.
 * This function spawns a child process using fork()
 * to execute the specified command along with provided arguments.
 * It waits for the child process to complete and
 * updates the exit status accordingly.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork(); /* Forks child process */
	if (child_pid == -1)
	{
		perror("Error:"); /* Print error message */
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126); /* Exit with defined status permission denied */
			exit(1);
		}
		/* TODO: ADD ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status)); /* Wait for child process to end execution */
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n"); /* Print err message */
		}
	}
}
