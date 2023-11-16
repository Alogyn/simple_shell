#include "shell.h"

/* Shell operations functions */

/**
  * interactive_mode - Check if the shell is running in interactive mode
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: 1 if the shell is in interactive mode, 0 otherwise
  */

int interactive_mode(data_t *data_use)
{
	/* Check if the standard input is associated with a terminal */
	/* read file descriptor is less than or equal to 2 */
	return (isatty(STDIN_FILENO) && data_use->read_file_descriptor <= 2);
}

/**
  * exit_shell - Exit the shell with a specified status or the default status
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: -2 to signal the shell to exit,
  * with the specified or default status
  */

int exit_shell(data_t *data_use)
{
	int converted_value;

	/* Check if a command-line argument is provided for the exit status */
	if (data_use->argv[1] != 0)
	{
		/* Convert the argument to an integer */
		converted_value = string_to_integer(data_use->argv[1]);

		/* Check if the conversion is successful */
		if (converted_value == -1)
		{
			/* Print an error message for an illegal number */
			data_use->status = 2;
			print_error(data_use, "Illegal number: ");
			_eputs(data_use->argv[1]);
			_eputchar('\n');
			return (1);
		}

		/* Set the error_number to the converted value */
		data_use->error_number = converted_value;
		/* Signal the shell to exit with the specified status */
		return (-2);
	}

	/* Set the default error_number for exit */
	data_use->error_number = -1;

	/* Signal the shell to exit with the default status */
	return (-2);
}

/**
  * change_directory - Change the current working directory
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: 0 on successful directory change, 1 on error
  */

int change_directory(data_t *data_use)
{
	char *str, *dir, buffer[1024];
	int temp_dir;

	str = getcwd(buffer, 1024);
	if (str == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (data_use->argv[1] == 0)
	{
		dir = get_environ_var(data_use, "HOME=");
		if (dir == NULL)
			temp_dir =
				chdir((dir = get_environ_var(data_use, "PWD=")) ? dir : "/");
		else
			temp_dir = chdir(dir);
	}
	else if (compare_string(data_use->argv[1], "-") == 0)
	{
		if (!get_environ_var(data_use, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(get_environ_var(data_use, "OLDPWD=")), _putchar('\n');
		temp_dir =
			chdir((dir = get_environ_var(data_use, "OLDPWD=")) ? dir : "/");
	}
	else
		temp_dir = chdir(data_use->argv[1]);
	if (temp_dir == -1)
	{
		print_error(data_use, "can't cd to ");
		_eputs(data_use->argv[1]), _eputchar('\n');
	}
	else
	{
		set_environ_variable(data_use, "OLDPWD", get_environ_var(data_use, "PWD="));
		set_environ_variable(data_use, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
  * help_shell - Display help information about the shell
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: 0 on successful execution
  */

int help_shell(data_t *data_use)
{
	char **arg_array;

	/* Get the array of arguments */
	arg_array = data_use->argv;

	/* Display a message indicating that the function is not yet implemented */
	_puts("help call works. Function not yet implemented \n");

	/* Unused condition, kept for future use */
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
  * find_shell - Find and execute the appropriate shell command
  *
  * @data_use: Pointer to the data structure containing information
  * about the shell
  *
  * Return: 0 on successful execution of the built-in command,
  * -1 if the command is not found
  */

int find_shell(data_t *data_use)
{
	int i = 0;
	/* Table of built-in commands with corresponding handlers */
	shellcmd_t shell_table[] = {
		{"exit", exit_shell},
		{"env", print_environ},
		{"help", help_shell},
		{"history", history_list},
		{"setenv", set_environ},
		{"unsetenv", remove_environ},
		{"cd", change_directory},
		{"alias", man_alias},
		{NULL, NULL}
	};

	/* Loop through the built-in command table */
	while (shell_table[i].command != NULL)
	{
		/* Check if the entered command matches a built-in command */
		if (compare_string(data_use->argv[0], shell_table[i].command) == 0)
		{
			/* Execute the corresponding handler func for the built-in cmd */
			data_use->line_count++;
			return (shell_table[i].handler(data_use));
		}
		i++;
	}

	/* Command not found in the built-in command table */
	return (-1);
}
