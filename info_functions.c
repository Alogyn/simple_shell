#include "shell.h"

/* Infos functions */

/**
  * set_info - Set information in the data structure based
  * on command line arguments
  *
  * @data_use: Pointer to the data structure containing shell information
  * @av: Array of strings representing command line arguments (char)
  *
  * Return: None
  */

void set_info(data_t *data_use, char **av)
{
	int i = 0;

	/* Set the filename from command line arguments */
	data_use->filename = av[0];

	/* Parse the argument to create argv */
	if (data_use->arg != 0)
	{
		data_use->argv = split_string(data_use->arg, " \t");
		/* Handle the case when split_string fails */
		if (data_use->argv == 0)
		{

			data_use->argv = malloc(2 * sizeof(char *));
			if (data_use->argv != 0)
			{
				data_use->argv[0] = duplicate_string(data_use->arg);
				data_use->argv[1] = NULL;
			}
		}

		/* Count the number of arguments in argv */
		while (data_use->argv && data_use->argv[i])
			i++;

		/* set argc based on the number of arguments */
		data_use->argc = i;

		/* Replace aliases and variables in argv */
		replace_alias(data_use);
		replace_variables(data_use);
	}
}

/**
  * free_info - Free memory allocated for shell information
  * in the data structure
  *
  * @data_use: Pointer to the data structure containing shell information
  * @global_set: Flag to indicate whether global data should be freed (int)
  *
  * Return : None
  */

void free_info(data_t *data_use, int global_set)
{
	/* Free memory allocated for argv */
	free_string(data_use->argv);
	data_use->argv = NULL;

	/* Set path to NULL */
	data_use->path = NULL;

	/* Free resources related to global_set */
	if (global_set)
	{
		/* Free argument if buffer_command is not set */
		if (data_use->buffer_command == 0)
			free(data_use->arg);

		/* Free environment variables list */
		if (data_use->env != 0)
			free_list(&(data_use->env));

		/* Free history list */
		if (data_use->history != 0)
			free_list(&(data_use->history));

		/* Free alias list */
		if (data_use->alias != 0)
			free_list(&(data_use->alias));

		/* Free environment string */
		free_string(data_use->environ);
			data_use->environ = NULL;

		/* Free buffer_command and close file descriptor */
		free_address((void **)data_use->buffer_command);
		if (data_use->read_file_descriptor > 2)
			close(data_use->read_file_descriptor);

		/* Flush the buffer */
		_putchar(BUFFER_FLUSH);
	}
}

/**
  * clear_info - Clear information in the data structure
  *
  * @data_use: Pointer to the data structure containing shell information
  *
  * Return: None
  */

void clear_info(data_t *data_use)
{
	/* Set argument, argc, argv, and path to NULL or zero */
	data_use->arg = NULL;
	data_use->argc = 0;
	data_use->argv = NULL;
	data_use->path = NULL;
}
