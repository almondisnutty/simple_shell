#include "shell.h"

/**
 * add_node - Function that adds a node to the beginning of the list.
 * @head: Address of pointer to the head node.
 * @str: string field of node.
 * @num: node index for history.
 *
 * Return: Pointer pointing to the recently added node.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t)); /*assign memory for added node */
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t)); /* Initialize the new node */
	new_head->num = num; /* Set the node index */
	if (str)
	{
		new_head->str = _strdup(str); /* Copy and set the string */
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head; /* Set the next pointer of the recently added node */
	*head = new_head; /* Updates the head pointer */
	return (new_head);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0)); /* Print the number of node */
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)"); /* Print the string or "(nil)" */
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i); /* Return the size of the list */
}

/**
 * get_node_index - Retrieves the index of a node within the linked list.
 * @head: Pointer pointing to the head of the list.
 * @node: Pointer pointing to the specific node in the list.
 *
 * Return: Index of the node or -1.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * list_to_strings - Converts a linked list of str into an arr of str.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1)); /* Allocate memory for str arr*/
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1); /* Designate memory for every str */
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]); /* Empty previously allocated strings */
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str); /* Dupli. the str into the allocated memory */
		strs[i] = str;
	}
	strs[i] = NULL; /* Set the last element of the array to NULL */
	return (strs);
}

/**
 * node_starts_with - Finds a node where the string begins
 * with the specified prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: Matches the character immediately following the specified prefix.
 *
 * Return: Matching node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


