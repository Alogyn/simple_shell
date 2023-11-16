#include "shell.h"

/* hsh function */

/**
  * hsh - Main function to execute the shell
  *
  * @data_use: Pointer to the data structure storing shell information
  * @argv: An array of strings representing command-line arguments (char)
  *
  * Return: The exit status or error number based on the exit condition
  */

int hsh(data_t *data_use, char **argv)
{
	int shell_return = 0;
	ssize_t ret_value = 0;

	while (ret_value != -1 && shell_return != -2)
	{
		clear_info(data_use);
		/* Display shell prompt in interactive mode or print newline */
		if (interactive_mode(data_use) != 0)
			_puts("$ ");
		_eputchar(BUFFER_FLUSH);
		ret_value = get_buffer(data_use);
		/* Process user input if no error occurred */
		if (ret_value != -1)
		{
			set_info(data_use, argv);
			shell_return = find_shell(data_use);
			if (shell_return == -1)
				find_command(data_use);
		}
		else if (interactive_mode(data_use) != 0)
			_putchar('\n');
		free_info(data_use, 0);
	}
	write_history(data_use);
	free_info(data_use, 1);
	/* Exit based on the exit condition or handle shell termination cdt */
	if (interactive_mode(data_use) == 0)
	{
		if (data_use->status != 0)
			exit(data_use->status);
	}
	if (shell_return == -2)
	{
		if (data_use->error_number == -1)
			exit(data_use->status);
		exit(data_use->error_number);
	}
	return (shell_return);
}
