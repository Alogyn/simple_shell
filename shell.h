#ifndef SHELL_H
#define SHELL_H

/* Standard Libreries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Buffer size macros */
#define MAX_BUFFER_SIZE 1024
#define READ_BUFFER		1024
#define WRITE_BUFFER	1024
#define BUFFER_FLUSH	-1

/* Chain command macros */
#define NORMAL_COMMAND	0
#define OR_COMMAND		1
#define AND_COMMAND		2
#define CHAIN_COMMAND	3

/* Convert number macros */
#define TO_LOWERCASE	1
#define TO_UNSIGNED		2

/* History file macros */
#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_SIZE	4096

/* Syscall macros */
#define SYS_GETLINE 0
#define SYS_STRTOK	0

/*  Environ extern variable call */
extern char **environ;

/* data_use initialization macros */
#define INIT_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
  * struct string_node - Node structure for a linked list of strings
  *
  * @index: Index of the node (int)
  * @str: Pointer to a string (char)
  * @next: Pointer to the next node in the linked list
  */

typedef struct string_node
{
	int index;
	char *str;
	struct string_node *next;
} node_t;

/**
  * struct data_env - Structure for shell data and environment
  *
  * @arg: The shell argument (char)
  * @argv: Array of shell arguments (char)
  * @path: The shell path (char)
  * @argc: Number of shell arguments (int)
  * @line_count: Line count in the shell (int)
  * @error_number: Error number in the shell (int)
  * @line_flag: Flag indicating line presence (int)
  * @filename: The shell filename (char)
  * @env: Pointer to the environment node
  * @history: Pointer to the history node
  * @alias: Pointer to the alias node
  * @environ: Array of environment strings (char)
  * @env_update: Flag indicating environment update (int)
  * @status: Status of the shell (int)
  * @buffer_command: Array of buffer commands (char)
  * @buffer_command_type: Type of buffer command (int)
  * @read_file_descriptor: File descriptor for reading (int)
  * @history_count: Count of shell history (int)
  */

typedef struct data_env
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_number;
	int line_flag;
	char *filename;
	node_t *env;
	node_t *history;
	node_t *alias;
	char **environ;
	int env_update;
	int status;
	char **buffer_command;
	int buffer_command_type;
	int read_file_descriptor;
	int history_count;
} data_t;

/**
  * struct shell_cmd - Structure for shell commands
  *
  * @command: The shell command (char)
  * @handler: Pointer to the function that handles the command (int)
  */

typedef struct shell_cmd
{
	char *command;
	int (*handler)(data_t *);
} shellcmd_t;

/* hsh function */
int hsh(data_t *data_use, char **argv);

/* String functions 1 */
int length_string(char *str);
char *duplicate_string(const char *str);
int compare_string(char *str1, char *str2);
char *strchar_locate(char *str, char c);

/* String functions 2 */
char *copy_string(char *dest, char *src);
char *copy_nstring(char *dest, char *src, int n);
char *concatenate_string(char *dest, char *src);
char *concatenate_nstring(char *dest, char *src, int n);

/* String functions 3 */
int check_delimiter(char c, char *delimiter);
char *check_needle(const char *haystack, const char *needle);
char **split_string(char *str, char *delimiter);
char **split_strdelim(char *str, char delimiter);

/* Print functions */
void _puts(char *str);
int _putchar(char c);
size_t print_list(const node_t *head);
size_t print_string_list(const node_t *head);

/* Memory functions */
char *set_memory(char *str, char c, unsigned int n);
void *realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size);
int free_address(void **ptr);
void free_string(char **pstr);

/* Print error functions */
void _eputs(const char *str);
int _putfd(char c, int file_descriptor);
int _putsfd(char *str, int file_descriptor);
int _eputchar(char c);
void print_error(data_t *, char *);

/* List functions 1 */
node_t *add_node(node_t **head, const char *str, int index);
node_t *add_node_end(node_t **head, const char *str, int index);
ssize_t get_node(node_t *head, node_t *node);
int delete_node(node_t **head, unsigned int index);

/* List functions 2 */
size_t length_list(const node_t *head);
void free_list(node_t **head_ptr);
char **string_list(node_t *head);
node_t *node_needle(node_t *node, char *prefix, char c);
int history_list(data_t *data_use);

/* Environ functions 1 */
char **get_environ(data_t *data_use);
char *get_environ_var(data_t *data_use, const char *name);
int set_environ(data_t *data_use);
int set_environ_variable(data_t *data_use, char *var, char *value);

/* Environ functions 2 */
int remove_environ(data_t *data_use);
int remove_environ_variable(data_t *data_use, char *var);
int list_environ(data_t *data_use);
int print_environ(data_t *data_use);

/* I\O files functions */
char *open_history(data_t *data_use);
int write_history(data_t *data_use);
int read_history(data_t *data_use);
int list_history(data_t *data_use, char *buffer, int linecount);
int renumber_history(data_t *data_use);

/* Alias functions */
int create_alias(data_t *data_use, char *str);
int replace_alias(data_t *data_use);
int print_alias(node_t *node);
int man_alias(data_t *data_use);
int delete_alias(data_t *data_use, char *str);

/* Path functions */
char *duplicate_character(char *source_str, int start, int stop);
int check_command(data_t *data_use, char *path);
char *find_path(data_t *data_use, char *source_str, char *cmd);
void find_command(data_t *data_use);
void fork_command(data_t *data_use);

/* Infos functions */
void set_info(data_t *data_use, char **av);
void free_info(data_t *data_use, int global_set);
void clear_info(data_t *data_use);

/* Shell operations functions */
int interactive_mode(data_t *data_use);
int exit_shell(data_t *data_use);
int change_directory(data_t *data_use);
int help_shell(data_t *data_use);
int find_shell(data_t *data_use);

/* Convert functions */
int str_to_int(char *str);
int string_to_integer(char *str);
char *integer_convert(long int value, int base, int flags);
int check_alphabetic(int c);

/* Syscall functions */
void handle_sigint(__attribute__((unused))int sig_num);
ssize_t write_buffer(data_t *data_use, char **buffer, size_t *length);
ssize_t get_buffer(data_t *data_use);
ssize_t read_buffer(data_t *data_use, char *buffer, size_t *i);
int _getline(data_t *data_use, char **ptr, size_t *length);

/* Chain functions */
int detect_chain(data_t *data_use, char *buffer, size_t *ptr);
void check_chain(data_t *data_use, char *buffer, size_t *ptr, size_t i, size_t length);

/* Alt functions */
int replace_string(char **old_str, char *new_str);
int replace_variables(data_t *data_use);
void delete_comments(char *buffer);
int print_decimal(int value, int file_descriptor);

#endif
