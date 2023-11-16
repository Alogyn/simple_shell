#include "shell.h"

/* Environ functions 2 */

/**
  * remove_environ - Remove environment variable(s)
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: 0 on success, 1 on failure
  */

int remove_environ(data_t *data_use)
{
	int i = 0;

	/* Check if there are enough arguments */
	if (data_use->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}

	/* Loop through the arguments */
	while (i + 1 <= data_use->argc)
	{
		/* Remove the corresponding environment variables */
		remove_environ_variable(data_use, data_use->argv[i + 1]);
		i++;
	}

	/* Return 0 on success */
	return (0);
}

/**
  * remove_environ_variable - Remove an environment variable
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  * @var: The environment variable to be removed (char)
  *
  * Return: 1 if the variable is removed, 0 otherwise
  */

int remove_environ_variable(data_t *data_use, char *var)
{
	node_t *node = data_use->env;
	size_t i;
	char *ptr;

	/* Check if the list is empty or the variable is NULL */
	if (node == NULL || var == NULL)
		return (0);

	/* Loop through the nodes to find */
	for (i = 0; node; i++)
	{
		ptr = check_needle(node->str, var);
		/* Check if the variable is found and remove it */
		if (ptr && *ptr == '=')
		{
			if (*ptr == '=')
			{
				/* Remove the specified variable */
				data_use->env_update = delete_node(&(data_use->env), i);
				i = 0;
				node = data_use->env;
				continue;
			}
		}
		node = node->next;
	}

	/* Return 1 if the variable is removed, 0 otherwise */
	return (data_use->env_update);
}

/**
  * list_environ - List environment variables and store
  * them in the data structure
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: 0 on success
  */

int list_environ(data_t *data_use)
{
	node_t *node = NULL;
	size_t i = 0;

	/* Loop through the global 'environ' variable */
	while (environ[i])
	{
		/* Add each variable to the linked list */
		add_node_end(&node, environ[i], 0);
		i++;
	}

	/* Update the 'data_use->env' with the newly created linked list */
	data_use->env = node;

	/* Return 0 on success */
	return (0);
}

/**
  * print_environ - Print the list of environment variables
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: 0 on success
  */

int print_environ(data_t *data_use)
{
	/* Use the print_string_list function to print the environment variables */
	print_string_list(data_use->env);

	/* Return 0 on success */
	return (0);
}
