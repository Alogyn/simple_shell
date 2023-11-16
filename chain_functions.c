#include "shell.h"

/* Chain functions */

/**
  * detect_chain - Detect and update the command type based
  * on the chaining operator
  *
  * @data_use: A pointer to the data structure containing shell information
  * @buffer: The input buffer containing the command line (char)
  * @ptr: A pointer to the position in the buffer
  *
  * Return: 1 if a chaining operator is detected, 0 otherwise
  */

int detect_chain(data_t *data_use, char *buffer, size_t *ptr)
{
	size_t j = *ptr;

	/* Check for '||' operator */
	if (buffer[j] == '|')
	{
		if (buffer[j + 1] == '|')
		{
			/* Replace '|' with null terminator */
			buffer[j] = '\0';
			j++;
			data_use->buffer_command_type = OR_COMMAND;
		}
	}
	/* Check for ';' operator */
	else if (buffer[j] == ';')
	{
		/* Replace ';' with null terminator */
		buffer[j] = '\0';
		data_use->buffer_command_type = CHAIN_COMMAND;
	}
	/* Check for '&&' operator */
	else if (buffer[j] == '&')
	{
		if (buffer[j + 1] == '&')
		{
			/* Replace '&' with null terminator */
			buffer[j] = '\0';
			j++;
			data_use->buffer_command_type = AND_COMMAND;
		}
	}
	/* Return 0 if no chaining operator is detected */
	else
		return (0);
	/* Update the position pointer */
	*ptr = j;
	/* Return 1 to indicate a chaining operator is detected */
	return (1);
}

/**
  * check_chain - Adjust the buffer based on the command type
  *
  * @data_use: Pointer to the data structure containing shell information
  * @buffer: Input buffer containing the command line (char)
  * @ptr: Pointer to the position in the buffer
  * @i: Current index in the buffer
  * @length: Length of the buffer
  *
  * Return: None
  */

void check_chain(data_t *data_use, char *buffer, size_t *ptr,
				size_t i, size_t length)
{
	size_t j = *ptr;

	/* Check for AND_COMMAND type */
	if (data_use->buffer_command_type == AND_COMMAND)
	{
		/* If the previous command had a non-zero exit status */
		if (data_use->status != 0)
		{
			/* Replace character at the current index with a null terminator */
			buffer[i] = '\0';
			/* Update the position pointer to the end of the buffer */
			j = length;
		}
	}
	/* Check for OR_COMMAND type */
	if (data_use->buffer_command_type == OR_COMMAND)
	{
		/* If the previous command had a zero exit status */
		if (data_use->status == 0)
		{
			/* Replace character at the current index with a null terminator */
			buffer[i] = '\0';
			/* Update the position pointer to the end of the buffer */
			j = length;
		}
	}
	/* Update the position pointer */
	*ptr = j;
}
