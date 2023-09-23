#include "shell.h"

/**
 * print_list_str - Prints only the string element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */

size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)"); /* Print the string or "(nil)" */
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i); /* Return the size of the list */
}

/**
 * add_node_end - Appends a node to the end of the list.
 * @head: Pointer to the head node.
 * @str: String value for the node.
 * @num: Index used for history.
 *
 * Return: Pointer to the newly appended node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t)); /* Designate memory for the new node */
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t)); /* Initialize the new node */
	new_node->num = num; /* Set the node index */
	if (str)
	{
		new_node->str = _strdup(str); /* Copy and set the string */
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node; /* Append the new node to the end of the list */
	}
	else
		*head = new_node; /* Update the head pointer if the list was empty */
	return (new_node);
}

/**
 * free_list - Frees all nodes in the list.
 * @head_ptr: Pointer to head node.
 *
 * Return: void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL; /* If a list is empty, set the head pointer to NULL */
}

/**
 * delete_node_at_index - Deletes a node at a given index.
 * @head: Pointer to first node.
 * @index: Index of the node to be deleted.
 *
 * Return: 1 if success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next; /* Update the head pointer */
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next; /* Update the previous node's next pointer */
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_len - Calculates the length of a linked list.
 * @h: Points to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
