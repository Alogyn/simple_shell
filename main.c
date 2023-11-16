#include "shell.h"

/* main function */

/**
  * open_error - Display an error message and exit when unable to open a file
  *
  * @program_name: The name of the program (executable)
  * @file_name: The name of the file that couldn't be opened
  *
  * Return: None
  */

void open_error(const char *program_name, const char *file_name)
{
	/* Print program name, error message, file name, and exit with status 2 */
	_eputs(program_name);
	_eputs(": 0: Can't open ");
	_eputs(file_name);
	_eputchar('\n');
	_eputchar(BUFFER_FLUSH);
	exit(127);
}

/**
  * main - Entry point for the shell program
  *
  * @argc: The number of command-line arguments
  * @argv: An array of strings representing the command-line arguments
  *
  * Return: EXIT_SUCCESS on successful execution, EXIT_FAILURE on failure
  */

int main(int argc, char *argv[])
{
	/* Initialize the data structure with default values */
	data_t data_use[] = { INIT_INFO };
	int file_descriptor = 2;

	/* Use inline assembly to modify the value of the file descriptor */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));

	/* Check if a file argument is provided */
	if (argc == 2)
	{
		/* Open the file for reading */
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			/* Handle file open errors */
			if (errno == ENOENT)
			{
				open_error(argv[0], argv[1]);
			}
			if (errno == EACCES)
				exit(126);
			return (EXIT_FAILURE);
		}
		data_use->read_file_descriptor = file_descriptor;
	}

	/* Read history, list environment variables, and execute the shell */
	read_history(data_use);
	list_environ(data_use);
	hsh(data_use, argv);

	/* Return EXIT_SUCCESS on successful execution */
	return (EXIT_SUCCESS);
}
