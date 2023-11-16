#include "shell.h"

/* Print functions */

/**
  * _puts - Print a string to standard output
  *
  * @str: The string to print (char)
  *
  * Return: None
  */

void _puts(char *str)
{
	int i;

	/* Check if the input string is NULL */
	if (!str)
		return;

	/* Loop through each character in the string */
	for (i = 0; str[i] != '\0'; i++)
		/* Call the _putchar function to print the character */
		_putchar(str[i]);
}

/**
  * _putchar - Write a single character to standard output
  *
  * @c: The character to be written (char)
  *
  * Return: On success, returns 1. On BUFFER_FLUSH or buffer full, returns 0
  */

int _putchar(char c)
{
	/* Index for the static buffer */
	static int i;
	/* Static buffer to accumulate characters */
	static char buffer[WRITE_BUFFER];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER - 1)
	{
		if (i > 0)
		{
			/* Write the buffer to standard output */
			write(1, buffer, i);
			i = 0;
		}
		if (c == BUFFER_FLUSH)
			/* Return 0 when BUFFER_FLUSH is encountered */
		return (0);
		}

	/* Add the character to the buffer */
	buffer[i++] = c;
	/* Return 1 on success */
	return (1);
}

/**
  * print_list - Print the elements of a linked list
  *
  * @head: Pointer to the head of the linked list
  *
  * Return: The number of elements in the linked list
  */

size_t print_list(const node_t *head)
{
	size_t i;

	for (i = 0; head; i++)
	{
		/* Print index */
		_puts(integer_convert(head->index, 10, 0));
		_putchar(':');
		_putchar(' ');
		/* Print string or (nil) if NULL */
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		/* Move to the next node in the linked list */
		head = head->next;
	}
	return (i);
}

/**
  * print_string_list - Print strings in a linked list
  *
  * @head: Pointer to the head of the linked list
  *
  * Return: Number of nodes in the list
  */

size_t print_string_list(const node_t *head)
{
	/* Counter for the number of nodes */
	size_t i;

	for (i = 0; head; i++)
	{
		/* Print the string or "(nil)" if NULL */
		_puts(head->str ? head->str : "(nil)");
		/* Print a newline character */
		_puts("\n");
		/* Move to the next node in the linked list */
		head = head->next;
	}
	return (i);
}
