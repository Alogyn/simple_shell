#include "shell.h"

/* String functions 2 */

/**
  * copy_string - Copies a string to another string
  *
  * @dest: The destination buffer (char)
  * @src: The source buffer (char)
  *
  * Return: A pointer to destination buffer
  */

char *copy_string(char *dest, char *src)
{
	int i;

	/* Check for self-copy or null source */
	if (dest == src || src == 0)
		return (dest);

	/* Copy characters until the null terminator is encountered */
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (dest);
}

/**
  * copy_nstring - Copies 'n' characters from a string to another string
  *
  * @dest: The destination buffer (char)
  * @src: The source buffer (char)
  * @n: The number of characters to copy (int)
  *
  * Return: A pointer to destination buffer
  */

char *copy_nstring(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	/* Copy char until we found 0 terminator or n char are copied */
	for (i = 0; src[i] != '\0' && i < n - 1; i++)
		dest[i] = src[i];

	/* Null-terminate the destination string if there is space left */
	if (i < n)
	{
		for (j = i; j < n; j++)
			dest[j] = '\0';
	}
	return (str);
}

/**
  * concatenate_string - Concatenates two strings
  *
  * @dest: The destination buffer (char)
  * @src: The source buffer (char)
  *
  * Return: A pointer to destination buffer
  */

char *concatenate_string(char *dest, char *src)
{
	int i, j;
	char *temp = dest;

	/* Find the null terminator in dest */
	for (i = 0; dest[i] != '\0'; i++)
		;

	/* Copy characters from src to dest */
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	/* Null-terminate the result */
	dest[i] = '\0';
	return (temp);
}

/**
  * concatenate_nstring - Concatenates 'n' characters from a string
  * to another string
  *
  * @dest: The destination buffer (char)
  * @src: The source buffer (char)
  * @n: The number of characters to concatenate (int)
  *
  * Return: A pointer to destination buffer
  */

char *concatenate_nstring(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	/* Find the null terminator in dest */
	for (i = 0; dest[i] != '\0'; i++)
		;

	/* Copy up to n characters from src to dest */
	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[i] = src[j];
		i++;
	}

	/* Null-terminate the result if there is space */
	if (j < n)
		dest[i] = '\0';
	return (str);
}
