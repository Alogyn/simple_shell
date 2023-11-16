#include "shell.h"

/* Memory functions */

/**
  * set_memory - Fills the first 'n' bytes of the memory area pointed to by
  * 'str' with the constant byte 'c'
  *
  * @str: Input pointer to memory area (char)
  * @c: Input constant byte (char)
  * @n: Input the Bytes filled (unsigned int)
  *
  * Return: ptemp pointer to 'str'
  */

char *set_memory(char *str, char c, unsigned int n)
{
	unsigned int fill = 0;

	/* Resoring value of 'c' in char 'str' pointer */
	while (fill < n)
	{
		*(str + fill) = c;
		fill++;
	}
	return (str);
}

/**
  * realloc_memory - Reallocates a memory block using malloc and free
  *
  * @ptr: Input allocated pointer memory (void)
  * @new_size: The new size of Bytes to allocate memory (int)
  * @old_size: The old size of Bytes to allocate memory (int)
  *
  * Return: A pointer to new memory, NULL if fail,
  * 'ptr' if the new and old size are equal,
  * NULL if 'new_size' == '0' and 'ptr' != NULL
  */

void *realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *char_ptr;
	unsigned int i = 0;

	/* In case new and old size are equal */
	if (new_size == old_size)
		return (ptr);
	/* In case the pointer *ptr is NULL */
	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		free(ptr);
		return (new_ptr);
	}
	/* In case new size is equal to '0' and the 'ptr' is NULL */
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	/* The memory allocation */
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	/* Allocate to pointer memory */
	char_ptr = ptr;
	while (i < old_size)
	{
		*(new_ptr + i) = *(char_ptr + i);
		i++;
	}
	free(ptr);
	return (new_ptr);
}

/**
  * free_address - Frees ptemp pointer and sets it to NULL
  *
  * @ptr: Pointer to the pointer to be freed (void)
  *
  * Return: 1 if success, 0 if fail
  */

int free_address(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		/* Set the pointer to NULL after freeing the memory */
		*ptr = NULL;
		return (1);
	}

	return (0);
}

/**
  * free_string - Frees an array of strings and sets the pointer to NULL
  *
  * @pstr: Pointer to the array of strings to be freed (char)
  *
  * Return: None
  */

void free_string(char **pstr)
{
	/* Temporary pointer to preserve the original pointer */
	char **ptemp = pstr;

	if (!pstr)
		return;
	while (*pstr)
		/* Free memory for each string in the array */
		free(*pstr++);
	/* Free memory used by the array */
	free(ptemp);
}
