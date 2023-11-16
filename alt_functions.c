#include "shell.h"

/* Alt functions */

/**
  * replace_string - Replace the content of an old string with a new string
  *
  * @old_str: Pointer to the old string (char)
  * @new_str: New string to replace the old string (char)
  *
  * Return: 1 on successful replacement, 0 if old_str is NULL
  */

int replace_string(char **old_str, char *new_str)
{
	/* Check if the old string is NULL */
	if (old_str == NULL)
		return (0);

	/* Free the memory occupied by the old string */
	free(*old_str);

	/* Replace the old string with the new string */
	*old_str = new_str;
	return (1);
}

/**
  * replace_variables - Replace variables in the command arguments
  * with their values
  *
  * @data_use: Pointer to the data structure holding
  * command-related information
  *
  * Return: 0 on successful replacement
  */

int replace_variables(data_t *data_use)
{
	int i = 0;
	node_t *node;

	for (i = 0; data_use->argv[i]; i++)
	{
		if (data_use->argv[i][0] != '$' || !data_use->argv[i][1])
			continue;

		if (!compare_string(data_use->argv[i], "$?"))
		{
			/* Replace "$?" with the exit status converted to string */
			replace_string(&(data_use->argv[i]),
				duplicate_string(integer_convert(data_use->status, 10, 0)));
			continue;
		}
		if (!compare_string(data_use->argv[i], "$$"))
		{
			/* Replace "$$" with the process ID converted to string */
			replace_string(&(data_use->argv[i]),
				duplicate_string(integer_convert(getpid(), 10, 0)));
			continue;
		}
		node = node_needle(data_use->env, &data_use->argv[i][1], '=');
		if (node)
		{
			/* Replace environment variables with their values */
			replace_string(&(data_use->argv[i]),
				duplicate_string(strchar_locate(node->str, '=') + 1));
			continue;
		}
		/* If the variable is not recognized, replace it with an empty str */
		replace_string(&data_use->argv[i], duplicate_string(""));
	}
	return (0);
}

/**
  * delete_comments - Remove comments from a buffer
  *
  * @buffer: Pointer to the buffer containing the command line input (char)
  *
  * Return: None
  */

void delete_comments(char *buffer)
{
	int i = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == '#')
		{
			/* Check if '#' is at the beginning of the line or after a space */
			if ((!i || buffer[i - 1] == ' '))
			{
				/* Remove the comment by null-terminating the string */
				buffer[i] = '\0';
				break;
			}
		}
		i++;
	}
}

/**
  * print_decimal - Print an integer to a file descriptor
  *
  * @value: The integer value to be printed
  * @file_descriptor: The file descriptor where the output is directed
  *
  * Return: The number of characters printed
  */

int print_decimal(int value, int file_descriptor)
{
	int (*output_char)(char) = (file_descriptor == STDERR_FILENO)
			? _eputchar : _putchar;
	int count = 0, power_of_ten = 1, digit;

	/* Handle negative numbers */
	if (value < 0)
	{
		output_char('-');
		count++;
		value = -value;
	}

	/* Find the largest power of 10 that is less than or equal to the value */
	while (power_of_ten <= value / 10)
	{
		power_of_ten *= 10;
	}

	/* Print each digit of the number */
	while (power_of_ten > 0)
	{
		digit = value / power_of_ten;
		output_char('0' + digit);
		count++;
		value %= power_of_ten;
		power_of_ten /= 10;
	}

	return (count);
}
