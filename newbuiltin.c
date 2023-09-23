#include "shell.h"
int _setenv(info_t *, char *, char *);

/**
 * _mycd - alter the shell process's current directory
 * @info: A pointer to a structure which holds prospective arguments.
 * This pointer is used to keep function prototypes consistent.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *current_path, *target_dir, buffer[1024];
	int chdir_result;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])/* Handles home directory change */
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_result = /* TODO: What exactly should this be? */
				chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)/* Handle the transition to prev*/
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_path);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = /* TODO: What exactly should this be? */
			chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)/* Store chdir success or error */
	{
		print_error(info, "Cannot change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhistory - The history list will be displayed with line numbers.
 * @info: A pointer to a structure which holds prospective arguments.
 * Determines if the shell is in interactive mode.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	/* Call this function to output the command history. */
	print_list(info->history);
	return (0);
}

/**
 * _myhelp - Display information for help
 * @info: A pointer to a structure which holds prospective arguments.
 * This pointer is used to keep function prototypes consistent.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* Unused workaround for the time being */
	return (0);
}
