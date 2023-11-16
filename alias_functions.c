#include "shell.h"

/* Alias functions */

/**
  * create_alias - Create or update an alias in the alias linked list
  *
  * @data_use: A pointer to the data structure containing the alias linked list
  * @str: The string representing the alias to be created or updated (char)
  *
  * Return: 0 on success, 1 if there is an error
  */

int create_alias(data_t *data_use, char *str)
{
	char *ptr;

	/* Locate the position of '=' in the input string */
	ptr = strchar_locate(str, '=');
	/* If '=' is not found, return 1 (error) */
	if (ptr == NULL)
		return (1);

	/* If '=' is at the end of the string */
	if (*ptr == 0)
		/* Delete the alias and return success */
		return (delete_alias(data_use, str));

	/* Delete the existing alias with the same name */
	delete_alias(data_use, str);

	/* Add a new node with the alias information to the alias linked list */
	return (add_node_end(&(data_use->alias), str, 0) == NULL);
}

/**
  * replace_alias - Replace the command with its alias
  *
  * @data_use: A pointer to the data structure containing the alias linked list
  *
  * Return: 1 on success, 0 if there is an error or no more replacements
  */

int replace_alias(data_t *data_use)
{
	node_t *node;
	int i = 0;
	char *ptr;

	/* Attempt up to 10 times to replace the command with its alias */
	while (i < 10)
	{
		/* Find the alias node with the same name as the command */
		node = node_needle(data_use->alias, data_use->argv[0], '=');

		/* If no alias is found, return 0 */
		if (!node)
			return (0);

		/* Free the original command string */
		free(data_use->argv[0]);

		/* Find the position of '=' in the alias value */
		ptr = strchar_locate(node->str, '=');

		/* If '=' is not found, return 0 */
		if (ptr == NULL)
			return (0);

		/* Duplicate the substring after '=' and update the command string */
		ptr = duplicate_string(ptr + 1);

		/* If the duplication fails, return 0 */
		if (ptr == NULL)
			return (0);

		/* Update the command string with the alias value */
		data_use->argv[0] = ptr;
		i++;
	}

	/* Return 1 if a replacement is successful */
	return (1);
}

/**
  * print_alias - Print the alias in the format: 'alias_name'='alias_value'
  *
  * @node: A pointer to the node containing the alias information
  *
  * Return: 0 on success, 1 if the node is NULL
  */

int print_alias(node_t *node)
{
	char *ptr = NULL, *a = NULL;

	/* Check if the node is not NULL */
	if (node)
	{
		/* Find the position of '=' in the alias string */
		ptr = strchar_locate(node->str, '=');
		a = node->str;

		/* Print the alias name up to the position of '=' */
		while (a <= ptr)
		{
			_putchar(*a);
			a++;
		}

		/* Print the rest of the alias string, enclosed in single quotes */
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");

		/* Return 0 on success */
		return (0);
	}

	/* Return 1 if the node is NULL */
	return (1);
}

/**
  * man_alias - Display information about aliases
  *
  * @data_use: A pointer to the data structure containing shell information
  *
  * Return: Always returns 0
  */

int man_alias(data_t *data_use)
{
	node_t *node = NULL;
	int i = 1;
	char *ptr = NULL;

	/* Check if argc is 1, indicating no arguments provided */
	if (data_use->argc == 1)
	{
		/* Display information for all aliases */
		node = data_use->alias;
		while (node != NULL)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	/* Iterate through the arguments */
	while (data_use->argv[i])
	{
		/* Check if the argument contains '=' */
		ptr = strchar_locate(data_use->argv[i], '=');

		/* Create a new alias if '=' is present */
		if (ptr)
			create_alias(data_use, data_use->argv[i]);

		/* Print the information of the specified alias */
		else
			print_alias(node_needle(data_use->alias, data_use->argv[i], '='));
		i++;
	}

	return (0);
}

/**
  * delete_alias - Delete an alias from the alias list
  *
  * @data_use: A pointer to the data structure containing shell information
  * @str: The alias to be deleted in the format 'alias_name=alias_value' (char)
  *
  * Return: 1 on success, 0 on failure
  */

int delete_alias(data_t *data_use, char *str)
{
	char *ptr, temp;
	int store_value;

	/* Locate '=' in the alias string */
	ptr = strchar_locate(str, '=');
	if (ptr == 0)
		/* Return 1 if '=' is not found in the alias string */
		return (1);

	/* Temporarily replace '=' with null terminator */
	temp = *ptr;
	*ptr = 0;

	/* Delete the node corresponding to the alias */
	store_value = delete_node(&(data_use->alias),
		get_node(data_use->alias, node_needle(data_use->alias, str, -1)));

	/* Restore the original value at the location of '=' */
	*ptr = temp;

	/* Return the result of the deletion operation */
	return (store_value);
}
