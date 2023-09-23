#include "shell.h"


/**
 * main - Starting point of the shell program.
 * @ac: Count of arguments.
 * @av: Argument vector.
 * Return: 0 for success, 1 for error.
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT }; /* Initialize the info_t struct */
	int fd = 2; /* File descriptor for the error output. */

	/* Assembly code written to manipulate the file descriptor. */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);/* Open a file with the intent to read from it. */
		if (fd == -1)
		{
			if (errno == EACCES) /* Access denied or lack of permission. */
				exit(126); /* Exit the program with an error code of 126. */
			if (errno == ENOENT) /* File or directory does not exist. */
			{
				_eputs(av[0]); /* Print the program name */
				_eputs(": 0: Can't open ");
				_eputs(av[1]); /* Print the file name */
				_eputchar('\n');
				_eputchar(BUF_FLUSH); /* Empty error buffer */
				exit(127); /* Exit the program with an error code of 127 */
			}
			return (EXIT_FAILURE); /* If open fails Return EXIT_FAILURE */
		}
		info->readfd = fd; /* Set the readfd field in the info struct. */
	}
	populate_env_list(info); /* Populate the environment list in the info struct*/
	read_history(info); /* Read command history from a file */
	hsh(info, av); /* Read command history from a file */
	return (EXIT_SUCCESS); /* If execution is successful Return EXIT_SUCCESS */
}
