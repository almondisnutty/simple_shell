#include "shell.h"

/**
 * find_path - Searches for the specified command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to locate.
 *
 * Return: Full path of command if found, or NULL if not.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd); /* Return command if it reps a valid execu path. */
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path); /* Return the full path if the executable is located. */
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL); /* Return NULL if exec is not found within the PATH. */
}

/**
 * dup_chars - Creates a copy of characters.
 * @pathstr: The PATH string.
 * @start: Starting point.
 * @stop: Stopping point.
 *
 * Return: Pointer to a new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf); /* Create a new buffer with char from start to stop index*/
}

/**
 * is_cmd - Determines whether a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 if not.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1); /* Return 1 if the file is a regular executable file. */
	}
	return (0);
}
