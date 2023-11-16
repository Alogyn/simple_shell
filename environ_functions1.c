#include "shell.h"

/* Environ functions 1 */

/**
  * get_environ - Get the environment variable list
  *
  * @data_use: Pointer to the data structure containing
  * information about the shell
  *
  * Return: A pointer to the environment variable list
  */

char **get_environ(data_t *data_use)
{
	/* Check if the environment or its update flag is null */
	if (!data_use->environ || data_use->env_update)
	{
		/* Refresh the environment variable list */
		data_use->environ = string_list(data_use->env);
		data_use->env_update = 0;
	}

	/* Return the pointer to the environment variable list */
	return (data_use->environ);
}

/**
  * get_environ_var - Get the value of an environment variable
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  * @name: Name of the environment variable (char)
  *
  * Return: A pointer to the value of the environment variable,
  * NULL if not found
  */

char *get_environ_var(data_t *data_use, const char *name)
{
	/* Traverse the environment variable list */
	node_t *node = data_use->env;
	char *ptr;

	while (node)
	{
		/* Check if the name is a prefix of the current environment variable */
		ptr = check_needle(node->str, name);
		if (ptr != NULL)
			if (*ptr != 0)
			return (ptr);
		/* Move to the next node in the list */
		node = node->next;
	}

	/* Return NULL if the environment variable is not found */
	return (NULL);
}

/**
  * set_environ - Set the value of an environment variable
  *
  * @data_use: Pointer to the data structure containing
  * information about the shell
  *
  * Return: 0 on success, 1 on failure
 */

int set_environ(data_t *data_use)
{
	/* Check if the correct number of arguments is provided */
	if (data_use->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}

	/* Attempt to set the environment variable */
	if (set_environ_variable(data_use, data_use->argv[1], data_use->argv[2]) != 0)
		return (0);

	/* Return 1 on failure */
	return (1);
}

/**
  * set_environ_variable - Set the value of an environment variable
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  * @var: Name of the environment variable (char)
  * @value: New value for the environment variable (char)
  *
  * Return: 0 on success, 1 on failure
  */

int set_environ_variable(data_t *data_use, char *var, char *value)
{
	node_t *node;
	char *buffer = NULL;
	char *ptr;

	/* Check if both variable name and value are provided */
	if (var == NULL || value == NULL)
		return (0);

	/* Allocate memory for the buffer to store the environment variable str */
	buffer = malloc(length_string(var) + length_string(value) + 2);
	if (buffer == 0)
		return (1);
	/* Create the environment variable string */
	copy_string(buffer, var);
	concatenate_string(buffer, "=");
	concatenate_string(buffer, value);
	/* Check if the environment variable already exists */
	node = data_use->env;
	while (node)
	{
		ptr = check_needle(node->str, var);
		if (ptr != NULL)
			if (*ptr == '=')
			{
				/* Update the existing environment variable */
				free(node->str);
				node->str = buffer;
				data_use->env_update = 1;
				return (0);
			}
		node = node->next;
	}
	/* Add the new environment variable to the end of the list */
	add_node_end(&(data_use->env), buffer, 0);
	/* Free the buffer and update the environment update flag */
	free(buffer);
	data_use->env_update = 1;
	/* Return 0 on success */
	return (0);
}
