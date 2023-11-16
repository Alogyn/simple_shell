#include "shell.h"

/* List functions 1 */

/**
  * add_node - Adds a new node at the beginning of a 'node_t' list
  *
  * @head: Pointer to the pointer of the head node
  * @str: String to be added to the new node (char)
  * @index: Integer value to be stored in the new node (int)
  *
  * Return: A pointer to the newly created node, or NULL if allocation fails
  */

node_t *add_node(node_t **head, const char *str, int index)
{
	node_t *new_node;

	/* Allocate memory for the new node */
	new_node = malloc(sizeof(node_t));
	if (new_node == NULL || head == NULL)
		return (NULL);

	/* Initialize the new node's memory */
	set_memory((void *)new_node, 0, sizeof(node_t));
	/* Set index and duplicate string if provided */
	new_node->index = index;

	if (str)
	{
		new_node->str = duplicate_string(str);
		if (!new_node->str)
		{
			/* Free allocated memory on failure */
			free(new_node);
			return (NULL);
		}
	}

	/* Add the new node to the beginning of the linked list */
	new_node->next = *head;
	*head = new_node;

	/* Return a pointer to the new head of the linked list */
	return (*head);
}

/**
  * add_node_end - Adds a new node at the end of a 'node_t' list
  *
  * @head: Pointer to the pointer to the head node
  * @str: String to be added to the new node (char)
  * @index: Integer value to be stored in the new node (int)
  *
  * Return: A pointer to the head of the updated linked list,
  * NULL if allocation fails
  */

node_t *add_node_end(node_t **head, const char *str, int index)
{
	node_t *new_node, *temp;

	/* Allocate memory for the new node */
	new_node = malloc(sizeof(node_t));
	if (new_node == NULL || head == NULL)
		return (NULL);

	/* Initialize the new node's memory */
	set_memory((void *)new_node, 0, sizeof(node_t));
	/* Set index and duplicate string if provided */
	new_node->index = index;
	if (str)
	{
		new_node->str = duplicate_string(str);
		if (!new_node->str)
		{
			/* Free allocated memory on failure */
			free(new_node);
			return (NULL);
		}
	}
	/* Traverse the linked list to find the end */
	temp = *head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	else
		*head = new_node;

	/* Return a pointer to the head of the linked list */
	return (*head);
}

/**
  * get_node - Gets the index of a specific node in a linked list
  *
  * @head: Pointer to the head of the linked list
  * @node: Pointer to the node whose index needs to be found
  *
  * Return: An index of a node, -1 if fail
  */

ssize_t get_node(node_t *head, node_t *node)
{
	size_t count;

	/* Traverse the linked list to find the node and return its index */
	for (count = 0; head != NULL; count++)
	{
		if (head == node)
			return (count);
		head = head->next;
	}

	/* Return -1 if the node is not found or head is NULL */
	return (-1);
}

/**
  * delete_node - Deletes a node at the specified index from a linked list
  *
  * @head: Pointer to the pointer to the head of the linked list
  * @index: Index of the node to be deleted (int)
  *
  * Return: 1 if success, 0 if fail.
  */

int delete_node(node_t **head, unsigned int index)
{
	unsigned int ind;
	node_t *temp, *prev_node;

	/* Check if the linked list is empty */
	if (*head == NULL)
		return (0);

	/* Delete the head node if the index is 0 */
	if (index == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	/* Traverse the linked list to find the node at the specified index */
	temp = *head;
	for (ind = 0; temp != NULL; ind++)
	{
		if (ind == index)
		{
			prev_node->next = temp->next;
			free(temp->str);
			free(temp);
			return (1);
		}
		prev_node = temp;
		temp = temp->next;
	}

	/* Return 0 if the node at the specified index is not found */
	return (0);
}
