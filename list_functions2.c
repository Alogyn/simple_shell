#include "shell.h"

/* List functions 2 */

/**
  * length_list - Calculate the length of a linked list
  *
  * @head: A pointer to the head of the linked list
  *
  * Return: The number of nodes in the linked list
  */

size_t length_list(const node_t *head)
{
	size_t length;

	/* Traverse the linked list and count nodes */
	for (length = 0; head != NULL; length++)
	{
		head = head->next;
	}
	return (length);
}

/**
  * free_list - Frees the memory occupied by a linked list
  *
  * @head_ptr: A pointer to the head of the linked list
  *
  * Return: None
  */

void free_list(node_t **head_ptr)
{
	node_t *node, *next_node, *current;

	/* Check if the head pointer or linked list is NULL */
	if (!head_ptr || !*head_ptr)
		return;
	current = *head_ptr;
	node = current;

	/*  Traverse the linked list and free memory for each node */
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	/* Set the head pointer to NULL */
	*head_ptr = NULL;
}

/**
  * string_list - Converts a linked list of strings into an array of strings
  *
  * @head: A pointer to the head of the linked list
  *
  * Return: An array of strings
  */

char **string_list(node_t *head)
{
	node_t *node = head;
	size_t length, j;
	char **strg;
	char *str;

	/* Calculate the length of the linked list */
	length = length_list(head);

	/*  Check if the linked list is empty */
	if (head == NULL || length == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	strg = malloc((length + 1) * sizeof(char *));
	if (!strg)
		return (NULL);

	/* Traverse the linked list and copy each string to the array */
	for (length = 0; node; node = node->next, length++)
	{
		/* Allocate memory for the string */
		str = malloc(length_string(node->str) + 1);
		if (str == NULL)
		{
			/* Free allocated memory on failure */
			for (j = 0; j < length; j++)
				free(strg[j]);
			free(strg);
			return (NULL);
		}

		/* Copy the string to the allocated memory */
		str = copy_string(str, node->str);
		strg[length] = str;
	}

	/* Set the last element of the array to NULL */
	strg[length] = NULL;
	return (strg);
}

/**
  * node_needle - Find a node in a linked list whose str starts with a prefix
  *
  * @node: A pointer to the head of the linked list
  * @prefix: The prefix to search for in the strings (char)
  * @c: Optional char to further filter the search. Use -1 to ignore (char)
  *
  * Return: A pointer to the found node, or NULL if not found
  */

node_t *node_needle(node_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	/* Traverse the linked list */
	while (node)
	{
		/* Check if the current node's str starts with the specified prefix */
		ptr = check_needle(node->str, prefix);
		/* If the prefix is found and matches the*/
		/* specified character (or ignored), return the current node */
		if (ptr && ((c == -1) || (*ptr == c)) && ptr)
			return (node);
		/* Move to the next node in the linked list */
		node = node->next;
	}

	/* Return NULL if no matching node is found */
	return (NULL);
}

/**
  * history_list - Print the contents of the history linked list
  *
  * @data_use: A pointer to the data structure containing
  * the history linked list
  *
  * Return: Always returns 0
  */

int history_list(data_t *data_use)
{
	/* Print the contents of the history linked list */
	print_list(data_use->history);

	/* Return 0 as the function always returns 0 */
	return (0);
}
