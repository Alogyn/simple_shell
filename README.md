# 0x16. C - Simple Shell - Low-level programming Group Project

Welcome to the ALX Low-Level Programming repository for the 'C - Simple Shell' project. In this challenging endeavor, you will undertake the creation of a simple Unix shell in the C programming language. A shell is the interface that allows users to interact with the operating system, executing commands and managing processes. This project is a comprehensive exploration of system calls, process creation, and command execution. This repository serves as your command center, containing scripts and C programs essential for developing your very own simple shell. Get ready to immerse yourself in the world of system programming as you design and implement a functional and efficient shell in C.

## Learning Objectives

By completing this project, you will:

- Understand the process of command execution in a shell, including parsing user input, creating child processes, and executing commands using system calls such as `fork`, `execvp`, and `wait`.
- Learn how to parse user input to extract command and argument information. Explore techniques for tokenizing input strings and handling whitespace.
- Implement built-in commands such as `cd` and `exit` within the shell, allowing users to navigate directories and gracefully exit the shell.
- Explore file I/O redirection and pipes to enable users to redirect input and output streams, as well as chain commands together.
- Implement signal handling to handle signals such as `Ctrl+C` (SIGINT) and `Ctrl+Z` (SIGTSTP), allowing users to interrupt or suspend command execution.

## Project Structure

The goal of this project is to develop a simple shell in the C programming language. A shell is a fundamental component of operating systems, allowing users to interact with the system through a command-line interface. This project will guide you through the process of creating a basic shell, including parsing user input, executing commands, and handling various features typical of a shell environment

- **[Shell Header](shell.h)**
    - **[shell.h()](shell.h)** The `shell.h` header file provides essential declarations and structures for building a shell program. It defines macros, data structures like `node_t` and `data_t`, and declares functions for string manipulation, list operations, memory management, file I/O, environment handling, history, aliases, and more. This header ensures modularity and clarity in implementing a shell program.

- **[main.c](main.c)**
    - **[void open_error()](main.c)** Display an error message and exit when unable to open a file. Takes the program name and the name of the file that couldn't be opened.

    - **[int main()](main.c)** Entry point for the shell program.

- **[hsh.c](hsh.c)**
    - **[int hsh()](hsh.c)** The `hsh` function is the main engine of the shell, overseeing user input processing, command execution, and shell termination. It initializes key structures, enters a loop to read and process user input, and handles both built-in and external commands. The function manages memory efficiently, writes command history, and ensures graceful error handling. It returns the exit status or error number based on the exit condition, providing a comprehensive and modular core for the shell's functionality.

- **[string_functions1.c](string_functions1.c)**
    - **[int length_string()](string_functions1.c)** Computes the length of a given null-terminated string. The function iterates through the characters of the string until the null terminator is encountered, excluding it from the count. If the input string is NULL, the function returns 0.

    - **[char *duplicate_string()](string_functions1.c)** Creates a duplicate of the provided null-terminated string. The function allocates memory for the new string and copies the characters from the input string in reverse order. If the input string is NULL or if memory allocation fails, the function returns NULL.

    - **[int compare_string()](string_functions1.c)** Performs a lexicographical comparison between two strings. The function iterates through the characters of both strings until a null terminator is reached in either string. It returns a positive integer if the first string is greater, a negative integer if the first string is smaller, and zero if the strings are equal.

    - **[char *strchar_locate()](string_functions1.c)** Locates the first occurrence of a specified character in a given string. The function iterates through the characters of the string until the target character is found or the null terminator is reached. If the character is found, the function returns a pointer to its first occurrence; otherwise, it returns NULL.

- **[string_functions2.c](string_functions2.c)**
    - **[char *copy_string()](string_functions2.c)** Copies the contents of one null-terminated string to another. The function ensures that the destination and source strings are not the same and that the source string is not NULL. It iterates through the characters of the source string, copying them to the destination string until the null terminator is encountered. The destination string is null-terminated after copying.

    - **[char *copy_nstring()](string_functions2.c)** Copies a specified number of characters from one string to another. The function takes a destination buffer, a source buffer, and the number of characters to copy. It copies characters from the source buffer to the destination buffer until the null terminator of the source is reached or until the specified number of characters (n - 1) is copied. The destination buffer is null-terminated, and the original destination buffer's address is returned.

    - **[char *concatenate_string()](string_functions2.c)** Concatenates two null-terminated strings. The function appends the characters from the source string to the end of the destination string. It finds the null terminator in the destination string and continues copying characters from the source string until the null terminator of the source string is reached. The resulting concatenated string is null-terminated, and the original destination buffer's address is returned.

    - **[char *concatenate_nstring()](string_functions2.c)** Concatenates a specified number of characters from one string to another. The function takes a destination buffer, a source buffer, and the number of characters to concatenate. It finds the null terminator in the destination buffer, then appends up to n characters from the source buffer to the destination buffer. The resulting string is null-terminated if there is space left, and the original destination buffer's address is returned.

- **[string_functions3.c](string_functions3.c)**
    - **[int check_delimiter()](string_functions3.c)** Checks if a given character is a delimiter within a specified string of delimiters. The function iterates through the characters in the delimiter string, returning 1 if the character matches any of the delimiters, and 0 otherwise.

    - **[char *check_needle()](string_functions3.c)** Checks if a specified substring (needle) is present at the beginning of a given string (haystack). The function returns a pointer to the location in the haystack after the needle if the needle is found at the beginning; otherwise, it returns NULL.

    - **[char **split_string]()](string_functions3.c)** Splits a string into an array of words based on a set of delimiters. The function counts the number of words in the string, allocates memory for an array of strings, and extracts individual words by skipping delimiters. If memory allocation fails, the function returns NULL.

    - **[char **split_strdelim()](string_functions3.c)** Splits a string into an array of words based on a single delimiter. The function counts the number of words in the string, allocates memory for an array of strings, and extracts individual words by skipping occurrences of the specified delimiter. If memory allocation fails, the function returns NULL.

- **[print_functions.c](print_functions.c)**
    - **[void _puts()](print_functions.c)** Print a string to standard output. Takes a pointer to the string (`str`).

    - **[int _putchar()](print_functions.c)** Write a single character to standard output. Takes a character (`c`). On success, returns 1. On BUFFER_FLUSH or buffer full, returns 0.

    - **[size_t print_list()](print_functions.c)** Print the elements of a linked list. Takes a pointer to the head of the linked list (`head`). Returns the number of elements in the linked list.

    - **[size_t print_string_list()](print_functions.c)** Print strings in a linked list. Takes a pointer to the head of the linked list (`head`). Returns the number of nodes in the list.

- **[print_error_functions.c](print_error_functions.c)**
    - **[void _eputs()](print_error_functions.c)** Prints a string to the standard error output. The function iterates through each character of the input string and uses `_eputchar` to print each character to the standard error output.

    - **[int _putfd()](print_error_functions.c)** Writes a character to a specified file descriptor or flushes the buffer. The function uses a static buffer and index to accumulate characters until the buffer is full or a flush signal (`BUFFER_FLUSH`) is received. It then flushes the buffer by writing its contents to the specified file descriptor.

    - **[int _putsfd()](print_error_functions.c)** Writes a string to a specified file descriptor. The function iterates through the input string, using `_putfd` to write each character to the specified file descriptor. It returns the total number of characters written.

    - **[int _eputchar()](print_error_functions.c)** Writes a character to the standard error file descriptor. The function uses a static buffer and index to accumulate characters until the buffer is full or a flush signal (`BUFFER_FLUSH`) is received. It writes the buffer to standard error if it is not empty. Returns 1 for successful write, -1 for BUFFER_FLUSH, and 0 otherwise.

    - **[void print_error(()](print_error_functions.c)** Prints an error message to the standard error. The function takes a pointer to a data structure (`data_t`) and an error message string (`estr`). It prints the filename, line count, command, and the error message to standard error using the previously defined `_eputs` and `print_decimal` functions.

- **[memory_functions.c](memory_functions.c)**
    - **[char *set_memory()](memory_functions.c)** ills the first `n` bytes of the memory area pointed to by `str` with the constant byte `c`. Takes a pointer to the memory area (`str`), a constant byte (`c`), and the number of bytes to fill (`n`). Returns the pointer to `str`.

    - **[void *realloc_memory()](memory_functions.c)** Reallocates a memory block using malloc and free. Takes an allocated pointer to memory (`ptr`), the new size of bytes to allocate memory (`new_size`), and the old size of bytes (`old_size`). Returns a pointer to the new memory, NULL if fail, `ptr` if the new and old sizes are equal, or NULL if `new_size` is 0 and `ptr` is not NULL.

    - **[int free_address()](memory_functions.c)** Frees the memory at the specified pointer and sets it to NULL. Takes a pointer to the pointer to be freed (`ptr`). Returns 1 if success, 0 if fail.

    - **[void free_string()](memory_functions.c)** Frees an array of strings and sets the pointer to NULL. Takes a pointer to the array of strings (`pstr`). Frees memory for each string in the array and then frees the memory used by the array.

- **[list_functions1.c](list_functions1.c)**
    - **[node_t *add_node()](list_functions1.c)** Adds a new node at the beginning of a 'node_t' list. Takes a pointer to the pointer of the head node, a string to be added to the new node, and an integer value to be stored in the new node. Allocates memory for the new node, initializes its memory, and adds it to the beginning of the linked list. Returns a pointer to the newly created node, or NULL if allocation fails.

    - **[node_t *add_node_end()](list_functions1.c)** Adds a new node at the end of a 'node_t' list. Takes a pointer to the pointer to the head node, a string to be added to the new node, and an integer value to be stored in the new node. Allocates memory for the new node, initializes its memory, and adds it to the end of the linked list. Returns a pointer to the head of the updated linked list, NULL if allocation fails.

    - **[ssize_t get_node()](list_functions1.c)** Gets the index of a specific node in a linked list. Takes a pointer to the head of the linked list and a pointer to the node whose index needs to be found. Traverses the linked list to find the node and returns its index. Returns -1 if the node is not found or head is NULL.

    - **[int delete_node()](list_functions1.c)** Deletes a node at the specified index from a linked list. Takes a pointer to the pointer to the head of the linked list and the index of the node to be deleted. Checks if the linked list is empty. Deletes the head node if the index is 0. Traverses the linked list to find the node at the specified index and deletes it. Returns 1 if successful, 0 if the node at the specified index is not found.

- **[list_functions2.c](list_functions2.c)**
    - **[size_t length_list()](list_functions2.c)** Calculate the length of a linked list. Takes a pointer to the head of the linked list. Traverse the linked list and count the number of nodes. Returns the number of nodes in the linked list.

    - **[void free_list()](list_functions2.c)** Frees the memory occupied by a linked list. Takes a pointer to the pointer to the head of the linked list. Traverse the linked list and free the memory for each node, including the strings. Sets the head pointer to NULL.

    - **[char **string_list()](list_functions2.c)** Converts a linked list of strings into an array of strings. Takes a pointer to the head of the linked list. Calculates the length of the linked list and allocates memory for the array of strings. Traverse the linked list, copy each string to the array, and set the last element of the array to NULL. Returns the array of strings.

    - **[node_t *node_needle()](list_functions2.c)** Finds a node in a linked list whose str starts with a prefix. Takes a pointer to the head of the linked list, a prefix to search for in the strings, and an optional character to further filter the search (use -1 to ignore). Traverse the linked list, check if the current node's str starts with the specified prefix and matches the specified character, and return the current node if found. Returns NULL if no matching node is found.


    - **[int history_list()](list_functions2.c)** Prints the contents of the history linked list. Takes a pointer to the data structure containing the history linked list. Calls the `print_list` function to print the contents of the history linked list. Always returns 0.

- **[environ_functions1.c](environ_functions1.c)**
    - **[char **get_environ()](environ_functions1.c)** Gets the environment variable list. If the environment or its update flag is null, it refreshes the environment variable list using the `string_list` function and updates the flag. Returns a pointer to the environment variable list.

    - **[char *get_environ_var()](environ_functions1.c)** Gets the value of an environment variable. It traverses the environment variable list, checking if the given `name` is a prefix of the current environment variable. Returns a pointer to the value of the environment variable or NULL if not found.

    - **[int set_environ()](environ_functions1.c)** Sets the value of an environment variable. Checks if the correct number of arguments (3) is provided and attempts to set the environment variable using the `set_environ_variable` function. Returns 0 on success, 1 on failure.

    - **[int set_environ_variable()](environ_functions1.c)** Sets the value of an environment variable. It allocates memory for a buffer to store the environment variable string, creates the string, and checks if the variable already exists. If it exists, it updates the existing environment variable; otherwise, it adds the new variable to the end of the list. Returns 0 on success, 1 on failure.

- **[environ_functions2.c](environ_functions2.c)**
    - **[int remove_environ()](environ_functions2.c)** Removes environment variable(s). Checks if there are enough arguments and loops through the arguments, removing the corresponding environment variables using the `remove_environ_variable` function. Returns 0 on success, 1 on failure.

    - **[int remove_environ_variable()](environ_functions2.c)** Removes an environment variable. It loops through the nodes of the environment variable list, finds the specified variable, and removes it using the `delete_node` function. Returns 1 if the variable is removed, 0 otherwise.

    - **[int list_environ()](environ_functions2.c)** Lists environment variables and stores them in the data structure. Loops through the global 'environ' variable and adds each variable to the linked list using the `add_node_end` function. Updates the 'data_use->env' with the newly created linked list. Returns 0 on success.

    - **[int print_environ()](environ_functions2.c)** Prints the list of environment variables. Uses the `print_string_list` function to print the environment variables from the linked list. Returns 0 on success.

- **[io_files_functions.c](io_files_functions.c)** 
    - **[char *open_history()](io_files_functions.c)** Constructs the path to the history file. Retrieves the home directory from environment variables using the `get_environ_var` function. Allocates memory for the history file path and initializes it with the home directory. Concatenates the path separator and the history file name. Returns a pointer to the dynamically allocated history file path on success, or NULL on failure or if the home directory is not available.

    - **[int write_history()](io_files_functions.c)** Writes the shell history to a file. Opens the history file for reading and writing, truncating it if it exists or creating it if not. Retrieves the file name using the `open_history` function. Writes each history entry followed by a newline to the history file. Flushes the buffer and closes the file. Returns 1 on success, -1 on failure.

    - **[int read_history()](io_files_functions.c)** Reads shell history from a file into the history list. Opens the history file for reading. Retrieves the file name using the `open_history` function. Reads the file size and allocates memory for the buffer. Reads the file content into the buffer and processes each line to add it to the history list. Frees the buffer and updates the history count. Returns the count of history entries read on success, 0 on failure.

    - **[int list_history()](io_files_functions.c)** Adds a history entry to the history list. Checks if the history list is not empty, and if so, sets the current node to the head of the list. Adds a new history entry to the end of the current history list using the `add_node_end` function. If the history list was initially empty, sets it to the new entry. Always returns 0 to indicate success.

    - **[int renumber_history()](io_files_functions.c)** Renumber the indices of history entries. Iterates through the history list and updates entry indices. Updates the history count with the total number of entries. Returns the total count of history entries after renumbering.

- **[alias_functions.c](alias_functions.c)**
    - **[int create_alias()](alias_functions.c)** Creates or updates an alias in the alias linked list. The function takes a pointer to a data structure (`data_t`) and a string representing the alias to be created or updated. It locates the position of '=' in the input string and, if '=' is not found, returns 1 (error). If '=' is at the end of the string, it deletes the alias and returns success. Otherwise, it deletes the existing alias with the same name and adds a new node with the alias information to the alias linked list.

    - **[int replace_alias()](alias_functions.c)** Replaces the command with its alias. The function takes a pointer to a data structure (`data_t`) and attempts up to 10 times to replace the command with its alias. It finds the alias node with the same name as the command, frees the original command string, and duplicates the substring after '=' to update the command string.

    - **[int print_alias()](alias_functions.c)** Prints the alias in the format: 'alias_name'='alias_value'. The function takes a pointer to a node containing the alias information and prints the alias name up to the position of '=', followed by the rest of the alias string enclosed in single quotes.

    - **[int man_alias()](alias_functions.c)** Displays information about aliases. The function takes a pointer to a data structure (`data_t`). If no arguments are provided, it displays information for all aliases. If arguments are provided, it iterates through the arguments, creating a new alias if '=' is present and printing the information of the specified alias.

    - **[int delete_alias()](alias_functions.c)** Deletes an alias from the alias list. The function takes a pointer to a data structure (`data_t`) and an alias to be deleted in the format 'alias_name=alias_value'. It locates '=' in the alias string, deletes the node corresponding to the alias, and returns 1 on success or 0 on failure.

- **[path_functions.c](path_functions.c)**
    - **[char *duplicate_character()](path_functions.c)** Duplicates a portion of a string, excluding ':' characters. Takes a source string, a starting index, and a stopping index (exclusive). Returns a pointer to the duplicated string.

    - **[int check_command()](path_functions.c)**  Checks if the given path corresponds to a regular file. Takes a pointer to the data structure (`data_t`) and a path. Ignores the data_use parameter for now. Returns 1 if the path corresponds to a regular file, 0 otherwise.

    - **[char *find_path()](path_functions.c)** Finds the full path of a command in the specified paths. Takes a pointer to the data structure (`data_t`), a string containing paths separated by colons, and a command to find in the paths. Checks if the command starts with "./" and if it corresponds to a regular file. Returns the full path of the command if found, NULL otherwise.

    - **[void find_command()](path_functions.c)** Finds and executes the specified command. Takes a pointer to the data structure (`data_t`). Sets the initial path to the command, increments the line count, and resets the line flag. Finds the path of the command in the specified paths using `find_path`. If found, sets the data_use path and forks a command. If not found, checks if the command is executable in the current directory or with an absolute path. Prints an error if the command is not found.

    - **[fork_command()](path_functions.c)** Forks a child process and executes the command. Takes a pointer to the data structure (`data_t`). Forks the child process and checks for fork failure. In the parent process, waits for the child process to complete and updates the status in the data structure. Handles special cases, such as permission denied. In the child process, executes the specified command using `execve`. If execution fails, exits with an appropriate status code.

- **[info_functions.c](info_functions.c)**
    - **[void set_info()](info_functions.c)** Sets information in a data structure based on command line arguments. The function takes a pointer to a data structure (`data_t`) and an array of strings representing command line arguments. It sets the filename from the command line arguments and parses the arguments to create the `argv` array. If parsing fails, it handles the case and sets `argv` with a single element containing the original argument. The function then counts the number of arguments in `argv`, sets `argc` accordingly, and replaces aliases and variables in `argv`.

    - **[void free_info()](info_functions.c)** Frees memory allocated for shell information in the data structure. The function takes a pointer to a data structure (`data_t`) and a flag (`global_set`). It frees the memory allocated for `argv`, sets `path` to NULL, and frees additional resources based on the value of `global_set`. If `global_set` is true, it frees the argument if `buffer_command` is not set, the environment variables list, history list, alias list, environment string, buffer_command, and closes the file descriptor

    - **[void clear_info()](info_functions.c)** Clears information in a data structure. The function takes a pointer to a data structure (`data_t`) and sets the argument, `argc`, `argv`, and `path` to NULL or zero, effectively clearing the information stored in the data structure.

- **[shell_operations_functions.c](shell_operations_functions.c)**
    - **[int interactive_mode()](shell_operations_functions.c)** Checks if the shell is running in interactive mode. Determines if the standard input is associated with a terminal (file descriptor less than or equal to 2). Returns 1 if the shell is in interactive mode, 0 otherwise.

    - **[int exit_shell()](shell_operations_functions.c)** Exits the shell with a specified status or the default status. Checks if a command-line argument is provided for the exit status. Converts the argument to an integer and sets the error_number to the converted value. Signals the shell to exit with the specified status. Returns -2 to signal the shell to exit with the specified or default status. If no argument is provided, sets the default error_number for exit.

    - **[int change_directory()](shell_operations_functions.c)** Changes the current working directory. Retrieves the current working directory using `getcwd`. Handles different cases based on the number of arguments and their values, such as changing to the home directory or the previous directory. Updates environment variables `PWD` and `OLDPWD` accordingly. Returns 0 on successful directory change, 1 on error.

    - **[int help_shell()](shell_operations_functions.c)** Displays help information about the shell. Prints a message indicating that the function is not yet implemented. Unused condition kept for future use. Returns 0 on successful execution.

    - **[int find_shell()](shell_operations_functions.c)** Finds and executes the appropriate shell command. Uses a table of built-in commands with corresponding handlers. Compares the entered command with the built-in command table and executes the corresponding handler function. Returns 0 on successful execution of the built-in command, -1 if the command is not found in the built-in command table.

- **[convert-functions.c](convert-functions.c)**
    - **[int str_to_int()](convert-functions.c)** Converts a string to an integer. It takes a string (`str`) as input and processes each character to build the corresponding integer value. Handles negative numbers and checks for overflow conditions.

    - **[int string_to_integer()](convert-functions.c)** Converts a string to an integer. Similar to `str_to_int`, it processes each character to build the corresponding integer value. Additionally, it checks for overflow conditions and returns -1 if encountered.

    - **[char *integer_convert()](convert-functions.c)** Converts a long integer to a string representation in a given base. It takes the `value` to be converted, the `base` for conversion, and `flags` for formatting. The result is stored in a static buffer, and a pointer to the string representation is returned.

    - **[int check_alphabetic()](convert-functions.c)** Checks if a character is alphabetic. It takes an integer (`c`) as input and uses the `isalpha` function to determine if the character is alphabetic. Returns 1 if the character is alphabetic, 0 otherwise.

- **[syscall_functions.c](syscall_functions.c)**
    - **[void handle_sigint()](syscall_functions.c)** Signal handler for SIGINT (Ctrl+C). Prints a newline, displays the shell prompt, and flushes the output buffer.

    - **[ssize_t write_buffer()](syscall_functions.c)** Reads input from the user and handles signals. Utilizes `_getline` (or `getline` if `SYS_GETLINE` is defined) to read input, removing the newline character if present. Updates the command history, length, and buffer_command in `data_use`. Returns the number of characters read on success, -1 on failure.

    - **[ssize_t get_buffer()](syscall_functions.c)** Reads input and handles signals, detects command chaining. Calls `write_buffer` to read input, then checks for command chaining using `detect_chain`. Updates `data_use->buffer_command_type`. Returns the number of characters read on success, -1 on failure.

    - **[ssize_t read_buffer()](syscall_functions.c)** Reads characters from the input file descriptor into the buffer. Returns the number of characters read on success, 0 if already read, -1 on failure.

    - **[int _getline(()](syscall_functions.c)** Custom implementation of `getline` to read input from the buffer. Utilizes `read_buffer` to read characters into the buffer. Handles newline characters and reallocation of memory. Returns the number of characters read on success, -1 on failure.

- **[chain_functions.c](chain_functions.c)**
    - **[int detect_chain()](chain_functions.c)** Detects and updates the command type based on the chaining operator. The function takes a pointer to a data structure (`data_t`) containing shell information, the input buffer containing the command line (`buffer`), and a pointer to the position in the buffer (`ptr`). It checks for chaining operators ('||', ';', '&&') in the buffer, updates the buffer command type accordingly, and returns 1 if a chaining operator is detected, or 0 otherwise.

    - **[void check_chain()](chain_functions.c)** Adjusts the buffer based on the command type. The function takes a pointer to a data structure (`data_t`) containing shell information, the input buffer containing the command line (`buffer`), a pointer to the position in the buffer (`ptr`), the current index in the buffer (`i`), and the length of the buffer (`length`). It checks the command type (AND_COMMAND or OR_COMMAND) and adjusts the buffer by replacing characters with null terminators based on the success or failure of the previous command.

- **[alt_functions.c](alt_functions.c)**
    - **[int replace_string()](alt_functions.c)** Replaces the content of an old string with a new string. The function takes a pointer to the old string (`old_str`) and a new string (`new_str`). It frees the memory occupied by the old string, replaces it with the new string, and returns 1 on successful replacement or 0 if `old_str` is NULL.

    - **[int replace_variables()](alt_functions.c)** Replaces variables in the command arguments with their values. The function takes a pointer to a data structure (`data_t`) holding command-related information. It iterates through the command arguments, replacing variables like "$?", "$$", and environment variables with their corresponding values. It returns 0 on successful replacement.

    - **[void delete_comments()](alt_functions.c)** Removes comments from a buffer. The function takes a pointer to a buffer containing the command line input. It iterates through the buffer and null-terminates the string at the position of a '#' character if it appears at the beginning of the line or after a space.

    - **[int print_decimal()](alt_functions.c)** Prints an integer to a file descriptor. The function takes an integer value (`value`) and a file descriptor (`file_descriptor`) where the output is directed (stdout or stderr). It handles negative numbers, prints each digit of the number, and returns the number of characters printed. The file descriptor is chosen based on whether it is stderr or stdout.

## Resources

### Read or watch:

- [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)

### man or help:

- `sh` (***Run `sh` as well***)

For detailed instructions and examples, refer to the respective script files in this repository.

---

## Authors

- **Mohamed Derfoufi**
[LinkedIn]() | [Twitter]() | [Instagram]()

- **Abderrahim Filali**
[LinkedIn]() | [Twitter]() | [Instagram]()

## Special Thanks for Project Guidance to 

- **Julien Barbier**

[YouTube](https://www.youtube.com/@0xJulien) | [Twitter](https://twitter.com/julienbarbier42) | [LinkedIn](https://www.linkedin.com/in/julienbarbier/)

## License

This project is licensed under the terms of the [MIT License](https://www.alxafrica.com/terms-conditions-portal/).

---

© 2023 [ALX](https://www.alxafrica.com/). All rights reserved.
