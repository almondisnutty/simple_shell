#include "shell.h"

/**
 * read_history - Reads the history from a history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: return number of history entries read, if failure occurs return 0.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY); /* Free history file for reading */
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize); /* Read the contents of the history file */
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++); /* Build list */
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX) /* Reduce list to HIST_MAX entries */
		delete_node_at_index(&(info->history), 0);
	renumber_history(info); /* Renumber the entries in history */
	return (info->histcount);
}

/**
 * write_history - Stores the history list in a history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644); /* free for writing */
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd); /* Note down each history entry to the file */
		_putfd('\n', fd); /* After each entry add a newline */
	}
	_putfd(BUF_FLUSH, fd); /* Empty the output buffer */
	close(fd);
	return (1);
}

/**
 * build_history_list - Appends an entry to the history linked list.
 * @info: Pointer to the info_t struct.
 * @buf: Buffer containing the history entry.
 * @linecount: Line count of the history entry.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount); /* Computing entry to the linked list */

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * get_history_file - Generates the path to the history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: Allocated str containing history file path, if fails return Null.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME="); /* Obtain the HOME directory from the enviro. */
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE); /* Join the HOME directory and history file name */
	return (buf);
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Pointer to the info_t struct.
 *
 * Return: The new histcount (number of history entries).
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++; /* Renumber the history entries */
		node = node->next;
	}
	return (info->histcount = i); /* Update the histcount */
}
