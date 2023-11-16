#include "shell.h"

/* Syscall functions */

/**
  * handle_sigint - Signal handler for SIGINT (Ctrl+C)
  *
  * @sig_num: Signal number (unused int)
  *
  * Return: None
  */

void handle_sigint(__attribute__((unused))int sig_num)
{
	/* Print a newline */
	_puts("\n");

	/* Display the shell prompt */
	_puts("$ ");

	/* Flush the output buffer */
	_putchar(BUFFER_FLUSH);
}

/**
  * write_buffer - Read input from the user and handle signals
  *
  * @data_use: Pointer to the data structure
  * @buffer: Pointer to the buffer to store the input (char)
  * @length: Pointer to the length of the input
  *
  * Return: The number of characters read on success, -1 on failure
  */

ssize_t write_buffer(data_t *data_use, char **buffer, size_t *length)
{
	ssize_t ret_value = 0;
	size_t ptr_length = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);

/* Read input using _getline or getline */
#if !SYS_GETLINE
		ret_value = _getline(data_use, buffer, &ptr_length);
#else
		ret_value = getline(buffer, &ptr_length, stdin);
#endif
		/* Process input if characters are read */
		if (ret_value > 0)
		{
			/* Remove the newline character if present */
			if ((*buffer)[ret_value - 1] == '\n')
			{
				(*buffer)[ret_value - 1] = '\0';
				ret_value--;
			}
			/* Set the line_flag to indicate new input */
			data_use->line_flag = 1;
			/* Delete comments from the input */
			delete_comments(*buffer);
			/* Update the command history */
			list_history(data_use, *buffer, data_use->history_count++);
			{
				/* Update the length and buffer_command in data_use */
				*length = ret_value;
				data_use->buffer_command = buffer;
			}
		}
	}
	return (ret_value);
}

/**
  * get_buffer - Read input and handle signals, detect command chaining
  *
  * @data_use: Pointer to the data structure
  *
  * Return: The number of characters read on success, -1 on failure
  */

ssize_t get_buffer(data_t *data_use)
{
	ssize_t ret_value = 0;
	static char *buffer;
	static size_t i, j, length;
	char *ptr, **ptr_buffer = &(data_use->arg);

	_putchar(BUFFER_FLUSH);
	ret_value = write_buffer(data_use, &buffer, &length);
	if (ret_value == -1)
		return (-1);
	if (length != 0)
	{
		j = i;
		ptr = buffer + i;

		check_chain(data_use, buffer, &j, i, length);
		while (j < length)
		{
			if (detect_chain(data_use, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			data_use->buffer_command_type = NORMAL_COMMAND;
		}

		*ptr_buffer = ptr;
		return (length_string(ptr));
	}

	*ptr_buffer = buffer;
	return (ret_value);
}

/**
  * read_buffer - Read characters from the input file descriptor
  * into the buffer
  *
  * @data_use: Pointer to the data structure
  * @buffer: Buffer to store the read characters (char)
  * @i: Pointer to the index to keep track of the current
  * position in the buffer
  *
  * Return: The number of characters read on success,
  * 0 if already read, -1 on failure
  */

ssize_t read_buffer(data_t *data_use, char *buffer, size_t *i)
{
	/* Variable to store the return value of the read system call */
	ssize_t ret_value = 0;

	/* Check if characters are already read */
	if (*i != 0)
		return (0);

	/* Read characters from the input file descriptor into the buffer */
	ret_value = read(data_use->read_file_descriptor, buffer, READ_BUFFER);

	/* Update the index with the number of characters read */
	if (ret_value >= 0)
		*i = ret_value;

	/* Return the number of characters read or -1 on failure */
	return (ret_value);
}

/**
  * _getline - Custom implementation of getline to read input from the buffer
  *
  * @data_use: Pointer to the data structure
  * @ptr: Pointer to the buffer to store the input (char)
  * @length: Pointer to the length of the buffer
  *
  * Return: The number of characters read on success, -1 on failure
  */

int _getline(data_t *data_use, char **ptr, size_t *length)
{
	static char buffer[MAX_BUFFER_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t ret_value = 0, str = 0;
	char *p = NULL, *new_ptr = NULL, *c;

	p = *ptr;
	if (p != 0)
	{
		if (length != 0)
			str = *length;
	}
	if (i == len)
		i = len = 0;

	ret_value = read_buffer(data_use, buffer, &len);
	if (ret_value == -1 || (ret_value == 0 && len == 0))
		return (-1);

	c = strchar_locate(buffer + i, '\n');
	j = c ? 1 + (unsigned int)(c - buffer) : len;
	new_ptr = realloc_memory(p, str, str ? str + j : j + 1);
	if (new_ptr == 0)
		return (p ? free(p), -1 : -1);

	if (str != 0)
		concatenate_nstring(new_ptr, buffer + i, j - i);
	else
		copy_nstring(new_ptr, buffer + i, j - i + 1);

	str += j - i;
	i = j;
	p = new_ptr;

	if (length != 0)
		*length = str;
	*ptr = p;
	return (str);
}
