#include "shell.h"

/* String functions 1 */

/**
  * length_string - Calculates the length of a string
  *
  * @str: Input string (char)
  *
  * Return: A length of a string
  */

int length_string(char *str)
{
	int length = 0;

	/* Check if a string is NULL */
	if (str == NULL)
		return (0);

	/* String length count */
	while (str[length] != '\0')
		length++;

	/* Return the length value */
	return (length);
}

/**
  * duplicate_string - Duplicates a string
  *
  * @str: Input string (char)
  *
  * Return: A pointer to the newly allocated duplicated string,
  * NULL if allocated memory fail
  */

char *duplicate_string(const char *str)
{
	int length = 0;
	char *dup;

	/* Check if a string is NULL */
	if (str == NULL)
		return (NULL);

	/* String length count */
	for (; *str++; length++)
		;

	/* Allocate memory */
	dup = malloc(sizeof(char) * (length + 1));

	/* Check if the success of allocation */
	if (!dup)
		return (NULL);

	/* Duplicate the string */
	for (length++; length--;)
		dup[length] = *--str;

	/* Return the duplicated string value */
	return (dup);
}

/**
  * compare_string - Compares two strings
  *
  * @str1: The first string (char)
  * @str2: The second string (char)
  *
  * Return: A positive integer if str1 > str2,
  * a negative integer if str1 < str2, a zero if str1 = str2
  */

int compare_string(char *str1, char *str2)
{
	int i;

	/* Iterate through the char of both str until a 0 terminator is reached */
	for (i = 0; str1[i] && str2[i]; i++)
	{
		/* Compare characters at the current position */
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}

	/* Check for equality at the end of the loop */
	if (str1[i] == str2[i])
		return (0);

	/* Return a comparison result based on ASCII value */
	else
		if (str1[i] < str2[i])
			return (-1);
		else
			return (1);
}

/**
  * strchar_locate - Locates a character in a string
  *
  * @str: Input string (char)
  * @c: The character to locate (char)
  *
  * Return: A pointer to the first occurrence of the character in the string,
  * NULL if 'c' not found
  */

char *strchar_locate(char *str, char c)
{
	/* Loop the char until the 0 terminator or the target char is found */
	while (*str && *str != c)
	{
		str++;
		}

	/* Check if the target character is found and return the pointer to it */
	if (*str == c)
		return (str);
	/* Otherwise return NULL */
	else
		return (NULL);
}
