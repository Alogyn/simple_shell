#include "shell.h"

/* Print error functions */

/**
  * _eputs - Print a string to the standard error output
  *
  * @str: The string to be printed (char)
  *
  * Return: None
  */

void _eputs(const char *str)
{
	int i = 0;

	/* Check if the input string is NULL */
	if (!str)
		return;

	/* Iterate through each character of the string */
	for (i = 0; str[i] != '\0'; i++)
	{
		/* Print the current character to the standard error output */
		_eputchar(str[i]);
	}
}

/**
  * _putfd - Write a character to a specified file descriptor
  * or flush the buffer
  *
  * @c: The character to be written or the BUFFER_FLUSH constant (char)
  * @file_descriptor: The file descriptor to write the character to (int)
  *
  * Return: 1 on successful write, -1 if BUFFER_FLUSH is passed
  */

int _putfd(char c, int file_descriptor)
{
	static int i;
	static char buffer[WRITE_BUFFER];

	/* Check if the buffer is full or BUFFER_FLUSH is passed */
	if (i >= WRITE_BUFFER || c == BUFFER_FLUSH)
	{
		/* Flush the buffer by writing its contents to the file descriptor */
		write(file_descriptor, buffer, i);
		/* Reset the buffer index to 0 */
		i = 0;
	}

	/* Check if the character is not BUFFER_FLUSH */
	if (c != BUFFER_FLUSH)
		/* Check if the character is not BUFFER_FLUSH */
		buffer[i++] = c;

	/* eturn 1 on successful write, -1 if BUFFER_FLUSH is passed */
	return (1);
}

/**
  * _putsfd - Write a string to a specified file descriptor
  *
  * @str: The string to be written (char)
  * @file_descriptor: The file descriptor to write the string to (int)
  *
  * Return: The total number of characters written on success,
  * 0 if the string is NULL or empty
  */

int _putsfd(char *str, int file_descriptor)
{
	int i = 0;

	/* Check if the string is NULL */
	if (!str)
		return (0);

	/* Iterate through the str and write each char to the file descriptor */
	while (*str)
	{
		i += _putfd(*str++, file_descriptor);
	}

	/* Return the total number of characters written */
	return (i);
}

/**
  * _eputchar - Write a character to the standard error file descriptor
  *
  * @c: The character to be written
  *
  * Return: 1 on successful write, -1 on BUFFER_FLUSH, and 0 otherwise
  */

int _eputchar(char c)
{
	/* Static variables for maintaining buffer state across calls */
	static int i;
	static char buffer[WRITE_BUFFER];

	/* Check if the character is a flush signal or the buffer is full */
	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER - 1)
	{
		/* If the buffer is not empty, write it to standard error */
		if (i > 0)
		{
			write(2, buffer, i);
			i = 0;
		}
		/* Return -1 if the character is a flush signal */
		if (c == BUFFER_FLUSH)
			return (-1);
	}

	/* Add the character to the buffer and increment the buffer index */
	buffer[i++] = c;

	/* Return 1 for successful write */
	return (1);
}

/**
  * print_error - Print an error message to the standard error
  *
  * @data_use: Pointer to the data structure containing relevant information
  * @estr: Error message string to be printed (char)
  *
  * Return: None
  */

void print_error(data_t *data_use, char *estr)
{
	/* Print filename, line count, cmd, and error message to standard error */
	_eputs(data_use->filename);
	_eputs(": ");
	print_decimal(data_use->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(data_use->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
