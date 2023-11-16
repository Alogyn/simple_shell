#include "shell.h"

/* I\O files functions */

/**
  * open_history - Construct the path to the history file
  *
  * @data_use: Pointer to the data structure containing shell information
  *
  * Return: On success, a pointer to the dynamic allocated history file path
  * On failure or if the home directory is not available, returns NULL
  */

char *open_history(data_t *data_use)
{
	char *hist_path, *home_dir;

	/* Retrieve the home directory from environment variables */
	home_dir = get_environ_var(data_use, "HOME=");
	if (home_dir == NULL)
		return (NULL);

	/* Allocate memory for the history file path */
	hist_path = malloc((length_string(home_dir) +
							length_string(HISTORY_FILE) + 2)
							* sizeof(char));
	if (hist_path == NULL)
		return (NULL);

	/* Initialize the history file path with the home directory */
	hist_path[0] = '\0';
	copy_string(hist_path, home_dir);

	/* Concatenate the path separator and the history file name */
	concatenate_string(hist_path, "/");
	concatenate_string(hist_path, HISTORY_FILE);
	return (hist_path);
}

/**
  * write_history - Write the shell history to a file
  *
  * @data_use: Pointer to the data structure containing shell information
  *
  * Return: On success, returns 1, on failure, returns -1
  */

int write_history(data_t *data_use)
{
	ssize_t file_descriptor;
	node_t *current_node = NULL;
	char *file_name = open_history(data_use);

	/* Check if opening the history file is successful */
	if (file_name == NULL)
		return (-1);

	/* Open the history file for reading and writing */
	/* Truncating it if it exists or creating it if not */
	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);

	/* Free the dynamically allocated file name string */
	free(file_name);

	/* Check if opening the file is successful */
	if (file_descriptor == -1)
		return (-1);

	/* Write each history entry followed by a newline to the history file */
	for (current_node = data_use->history; current_node; current_node =
					current_node->next)
	{
		_putsfd(current_node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}

	/* Flush the buffer and close the file */
	_putfd(BUFFER_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
  * read_history - Read shell history from a file into the history list
  *
  * @data_use: Pointer to the data structure containing shell information
  *
  * Return: On success, returns the count of history entries read
  * On failure, returns 0
  */

int read_history(data_t *data_use)
{
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	int i, last = 0, line_count = 0;
	char *buffer = NULL;
	char *file_name = open_history(data_use);

	if (file_name == NULL)
		return (0);
	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc((file_size + 1) * sizeof(char));
	if (buffer == NULL)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = '\0';
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			list_history(data_use, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		list_history(data_use, buffer + last, line_count++);
	free(buffer);
	data_use->history_count = line_count;
	while (data_use->history_count-- >= HISTORY_SIZE)
		delete_node(&(data_use->history), 0);
	renumber_history(data_use);
	return (data_use->history_count);
}

/**
  * list_history - Add a history entry to the history list
  *
  * @data_use: Pointer to the data structure containing shell information
  * @buffer: The history entry to be added (char)
  * @line_count: The line count of the history entry (int)
  *
  * Return: Always returns 0 to indicate success
  */

int list_history(data_t *data_use, char *buffer, int line_count)
{
	node_t *current_node = NULL;

	/* Check if the history list is not empty */
	if (data_use->history)
		current_node = data_use->history;

	/* Add a new history entry to the end of the current history list */
	add_node_end(&current_node, buffer, line_count);

	/* If the history list was initially empty, set it to the new entry */
	if (data_use->history == NULL)
		data_use->history = current_node;

	/* Always return 0 to indicate success */
	return (0);
}

/**
  * renumber_history - Renumber the indices of history entries
  *
  * @data_use: Pointer to the data structure containing shell information
  *
  * Return: The total count of history entries after renumbering
  */

int renumber_history(data_t *data_use)
{
	node_t *current_node = data_use->history;
	int i = 0;

	/* Iterate through the history list and update entry indices */
	while (current_node != NULL)
	{
		current_node->index = i++;
		current_node = current_node->next;
	}

	/* Update the history count with the total number of entries */
	return (data_use->history_count = i);
}
