#include "shell.h"

/* String functions 3 */

/**
  * check_delimiter - Check if a character is a delimiter
  *
  * @c: The character to check (char)
  * @delimiter: The string of delimiters (char)
  *
  * Return: 1 if the character is a delimiter, 0 otherwise
  */

int check_delimiter(char c, char *delimiter)
{
	int i;

	for (i = 0; delimiter[i]; i++)
	{
		if (delimiter[i] == c)
			return (1);
	}

	return (0);
}

/**
  * check_needle - Check if a needle is present at the beginning of a haystack
  *
  * @haystack: The string to search (char)
  * @needle: The substring to check for (char)
  *
  * Return: A pointer to the location in @haystack after @needle,
  * NULL if @needle is not found at the beginning of @haystack
  */

char *check_needle(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
  * split_string - Split a string into an array of words based on delimiters
  *
  * @str: The string to split
  * @delimiter: The string of delimiters
  *
  * Return: An array of strings or NULL if memory allocation fails
  */

char **split_string(char *str, char *delimiter)
{
	int i, j, k, m, word_number = 0;
	char **strg;

	if (str == NULL)
		return (NULL);
	if (delimiter == NULL)
		delimiter = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!check_delimiter(str[i], delimiter) &&
				(check_delimiter(str[i + 1], delimiter) || !str[i + 1]))
			word_number++;
	if (word_number == 0)
		return (NULL);
	strg = malloc((1 + word_number) * sizeof(char *));
	if (!strg)
		return (NULL);
	for (i = j = 0; j < word_number; j++)
	{
		while (check_delimiter(str[i], delimiter))
			i++;
		for (k = 0; !check_delimiter(str[i + k], delimiter) && str[i + k]; k++)
			;
		strg[j] = malloc((k + 1) * sizeof(char));
		if (strg[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(strg[k]);
			free(strg);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			strg[j][m] = str[i++];
		strg[j][m] = '\0';
	}
	strg[j] = NULL;
	return (strg);
}

/**
  * split_strdelim - Split a string into an array of words
  * based on a single delimiter
  *
  * @str: The string to split
  * @delimiter: The delimiter character
  *
  * Return: An array of strings or NULL if memory allocation fails
  */

char **split_strdelim(char *str, char delimiter)
{
	int i, j, k, m, word_number = 0;
	char **strg;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
		    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			word_number++;
	if (word_number == 0)
		return (NULL);
	strg = malloc((1 + word_number) * sizeof(char *));
	if (!strg)
		return (NULL);
	for (i = j = 0; j < word_number; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		for (k = 0; str[i + k] != delimiter &&
						str[i + k] && str[i + k] != delimiter; k++)
			;
		strg[j] = malloc((k + 1) * sizeof(char));
		if (strg[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(strg[k]);
			free(strg);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			strg[j][m] = str[i++];
		strg[j][m] = '\0';
	}
	strg[j] = NULL;
	return (strg);
}
