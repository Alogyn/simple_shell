#include "shell.h"

/* Path functions */

/**
  * duplicate_character - Duplicate a portion of a string
  *
  * @source_str: The source string (char)
  * @start: The starting index of the portion to duplicate (int)
  * @stop: The stopping index (exclusive) of the portion to duplicate (int)
  *
  * Return: A pointer to the duplicated string
  */

char *duplicate_character(char *source_str, int start, int stop)
{
	static char buffer[MAX_BUFFER_SIZE];
	int i = start, j = 0;

	/* Iterate through the specified portion of the string */
	while (i < stop)
	{
		/* Exclude ':' characters while copying */
		if (source_str[i] != ':')
			buffer[j++] = source_str[i];
		i++;
	}
	/* Null-terminate the resulting string */
	buffer[j] = '\0';

	return (buffer);
}

/**
  * check_command - Check if the given path corresponds to a regular file
  *
  * @data_use: Pointer to the data structure
  * @path: Path to the file (char)
  *
  * Return: 1 if the path corresponds to a regular file, 0 otherwise
  */

int check_command(data_t *data_use, char *path)
{
	struct stat file_stat;

	/* Ignore the data_use parameter for now */
	(void)data_use;

	/* Check if the path is valid and gather information about the file */
	if (!path || stat(path, &file_stat))
		return (0);

	/* Check if the file is a regular file */
	if (file_stat.st_mode & S_IFREG)
	{
		/* Path corresponds to a regular file */
		return (1);
	}

	/* Path does not correspond to a regular file */
	return (0);
}

/**
  * find_path - Find the full path of a command in the specified paths
  *
  * @data_use: Pointer to the data structure
  * @source_str: String containing the paths separated by colons (char)
  * @cmd: Command to find in the paths (char)
  *
  * Return: Full path of the command if found, NULL otherwise
  */

char *find_path(data_t *data_use, char *source_str, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!source_str)
		return (NULL);
	if ((length_string(cmd) > 2))
	{
		if (check_needle(cmd, "./"))
		{
			if (check_command(data_use, cmd))
				return (cmd);
		}
	}
	while (1)
	{
		if (source_str[i] == 0 || source_str[i] == ':')
		{
			path = duplicate_character(source_str, current_position, i);
			if (*path == 0)
				concatenate_string(path, cmd);
			else
			{
				concatenate_string(path, "/");
				concatenate_string(path, cmd);
			}
			if (check_command(data_use, path))
				return (path);
			if (source_str[i] == 0)
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}

/**
  * find_command - Find and execute the specified command
  *
  * @data_use: Pointer to the data structure
  *
  * Return: None
  */

void find_command(data_t *data_use)
{
	int i = 0, j = 0;
	char *path = NULL;

	data_use->path = data_use->argv[0];
	if (data_use->line_flag == 1)
	{
		data_use->line_count++;
		data_use->line_flag = 0;
	}
	while (data_use->arg[i])
	{
		if (!check_delimiter(data_use->arg[i], " \t\n"))
			j++;
		i++;
	}
	if (j == 0)
		return;

	path = find_path(data_use, get_environ_var(data_use, "PATH="),
					data_use->argv[0]);
	if (path != 0)
	{
		data_use->path = path;
		fork_command(data_use);
	}
	else
	{
		if ((interactive_mode(data_use) || get_environ_var(data_use, "PATH=")
			|| data_use->argv[0][0] == '/') && check_command(data_use,
					data_use->argv[0]))
			fork_command(data_use);
		else if (*(data_use->arg) != '\n')
		{
			data_use->status = 127;
			print_error(data_use, "not found\n");
		}
	}
}

/**
  * fork_command - Fork a child process and execute the command
  *
  * @data_use: Pointer to the data structure
  *
  * Return: None
  */

void fork_command(data_t *data_use)
{
	pid_t child_pid;

	/* Fork the child process */
	child_pid = fork();
	/* Check for fork failure */
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	/* Parent process */
	if (child_pid != 0)
	{
		/* Wait for the child process to complete */
		wait(&(data_use->status));
		/* Check if the child process exited normally */
		if (WIFEXITED(data_use->status))
		{
			/* Update the status in the data structure */
			data_use->status = WEXITSTATUS(data_use->status);
			/* Handle special case when permission is denied */
			if (data_use->status == 126)
				print_error(data_use, "Permission denied\n");
		}
	}
	/* Child process */
	else
	{
		/* Execute the specified command in the child process */
		if (execve(data_use->path, data_use->argv, get_environ(data_use)) == -1)
		{
			free_info(data_use, 1);
			/* Exit with 126 if permission is denied, otherwise exit with 1 */
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
}
