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

- **[shell.h](shell.h)**
    - **()** 

- **[main.c](main.c)**
    - **()**

- **[hsh.c](hsh.c)**
    - **()**

- **[string_functions1.c](string_functions1.c)**
    - **length_string()** Computes the length of a given null-terminated string. The function iterates through the characters of the string until the null terminator is encountered, excluding it from the count. If the input string is NULL, the function returns 0.

    - **duplicate_string()** Creates a duplicate of the provided null-terminated string. The function allocates memory for the new string and copies the characters from the input string in reverse order. If the input string is NULL or if memory allocation fails, the function returns NULL.

    - **compare_string()** Performs a lexicographical comparison between two strings. The function iterates through the characters of both strings until a null terminator is reached in either string. It returns a positive integer if the first string is greater, a negative integer if the first string is smaller, and zero if the strings are equal.

    - **strchar_locate()** Locates the first occurrence of a specified character in a given string. The function iterates through the characters of the string until the target character is found or the null terminator is reached. If the character is found, the function returns a pointer to its first occurrence; otherwise, it returns NULL.

- **[string_functions2.c](string_functions2.c)**
    - **copy_string()** Copies the contents of one null-terminated string to another. The function ensures that the destination and source strings are not the same and that the source string is not NULL. It iterates through the characters of the source string, copying them to the destination string until the null terminator is encountered. The destination string is null-terminated after copying.

    - **copy_nstring()** Copies a specified number of characters from one string to another. The function takes a destination buffer, a source buffer, and the number of characters to copy. It copies characters from the source buffer to the destination buffer until the null terminator of the source is reached or until the specified number of characters (n - 1) is copied. The destination buffer is null-terminated, and the original destination buffer's address is returned.

    - **concatenate_string()** Concatenates two null-terminated strings. The function appends the characters from the source string to the end of the destination string. It finds the null terminator in the destination string and continues copying characters from the source string until the null terminator of the source string is reached. The resulting concatenated string is null-terminated, and the original destination buffer's address is returned.

    - **concatenate_nstring()** Concatenates a specified number of characters from one string to another. The function takes a destination buffer, a source buffer, and the number of characters to concatenate. It finds the null terminator in the destination buffer, then appends up to n characters from the source buffer to the destination buffer. The resulting string is null-terminated if there is space left, and the original destination buffer's address is returned.

- **[string_functions3.c](string_functions3.c)**
    - **[int length_string(char *str)](string_functions3.c)** Checks if a given character is a delimiter within a specified string of delimiters. The function iterates through the characters in the delimiter string, returning 1 if the character matches any of the delimiters, and 0 otherwise.

    - **[char *duplicate_string(const char *str)](string_functions3.c)** Checks if a specified substring (needle) is present at the beginning of a given string (haystack). The function returns a pointer to the location in the haystack after the needle if the needle is found at the beginning; otherwise, it returns NULL.

    - **[int compare_string(char *str1, char *str2)](string_functions3.c)** Splits a string into an array of words based on a set of delimiters. The function counts the number of words in the string, allocates memory for an array of strings, and extracts individual words by skipping delimiters. If memory allocation fails, the function returns NULL.

    - **[char *strchar_locate(char *str, char c)](string_functions3.c)** Splits a string into an array of words based on a single delimiter. The function counts the number of words in the string, allocates memory for an array of strings, and extracts individual words by skipping occurrences of the specified delimiter. If memory allocation fails, the function returns NULL.

- **[print_-nctions.c](print_-nctions.c)**
    - **()**

- **[print_error_functions.c](print_error_functions.c)**
    - **()**

- **[memory_functions.c](memory_functions.c)**
    - **()**

- **[list_functions1.c](list_functions1.c)**
    - **()**

- **[list_functions2.c](list_functions2.c)**
    - **()**

- **[environ_functions1.c](environ_functions1.c)**
    - **()**

- **[environ_functions2.c](environ_functions2.c)**
    - **()**

- **[io_files_functions.c](io_files_functions.c)**
    - **()**

- **[alias_functions.c](alias_functions.c)**
    - **()**

- **[path_functions.c](path_functions.c)**
    - **()**

- **[info_functions.c](info_functions.c)**
    - **[void set_info(data_t *data_use, char **av)](info_functions.c)** Sets information in a data structure based on command line arguments. The function takes a pointer to a data structure (`data_t`) and an array of strings representing command line arguments. It sets the filename from the command line arguments and parses the arguments to create the `argv` array. If parsing fails, it handles the case and sets `argv` with a single element containing the original argument. The function then counts the number of arguments in `argv`, sets `argc` accordingly, and replaces aliases and variables in `argv`.

    - **[void free_info(data_t *data_use, int global_set)](info_functions.c)** Frees memory allocated for shell information in the data structure. The function takes a pointer to a data structure (`data_t`) and a flag (`global_set`). It frees the memory allocated for `argv`, sets `path` to NULL, and frees additional resources based on the value of `global_set`. If `global_set` is true, it frees the argument if `buffer_command` is not set, the environment variables list, history list, alias list, environment string, buffer_command, and closes the file descriptor

    - **[void clear_info(data_t *data_use)](info_functions.c)** Clears information in a data structure. The function takes a pointer to a data structure (`data_t`) and sets the argument, `argc`, `argv`, and `path` to NULL or zero, effectively clearing the information stored in the data structure.

- **[shell_operations_functions.c](shell_operations_functions.c)**
    - **()**

- **[convert-functions.c](convert-functions.c)**
    - **()**

- **[syscall_functions.c](syscall_functions.c)**
    - **()**

- **[chain_functions.c](chain_functions.c)**
    - **()**

- **[alt_functions.c](alt_functions.c)**
    - **()**

## Resources

### Read or watch:

- []()

### man or help:

- ``

For detailed instructions and examples, refer to the respective script files in this repository.

---

## Authors

- **Mohamed Derfoufi**

- **Abderrahim Filali**

## Special Thanks for Project Guidance to 

- **Julien Barbier**

[YouTube](https://www.youtube.com/@0xJulien) | [Twitter](https://twitter.com/julienbarbier42) | [LinkedIn](https://www.linkedin.com/in/julienbarbier/)

## License

This project is licensed under the terms of the [MIT License](https://www.alxafrica.com/terms-conditions-portal/).

---

© 2023 [ALX](https://www.alxafrica.com/). All rights reserved.