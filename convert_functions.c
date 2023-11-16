#include "shell.h"

/* Convert functions */

/**
  * str_to_int - Convert a string to an integer
  *
  * @str: The input string to convert (char)
  *
  * Return: The converted integer value
  */

int str_to_int(char *str)
{
	int convert = 0, length = 0, sign = 1, i = 0;

	/* Count the length of the string */
	while (str[length] != '\0')
	{
		length++;
	}

	/* Loop for conversion*/
	for (; i < length; i++)
	{
		if (str[i] == '-')
		{
			/* Handle negative sign */
			sign = -sign;
		}

		else if (str[i] >= '0' && str[i] <= '9')
		{
			/* Check for overflow before updating the conversion */
			if (convert > (INT_MAX - (str[i] - '0')) / 10)
			{
				return ((sign == 1) ? INT_MAX : INT_MIN);
			}
			convert = convert * 10 + (str[i] - '0');
		}
		else if (convert != 0)
		{
			/* Stop if non-numeric characters appear after a valid number */
			break;
		}
	}
	return (convert * sign);
}

/**
  * string_to_integer - Convert a string to an integer
  *
  * @str: The input string to convert (char)
  *
  * Return: The converted integer value, or -1 if the conversion fails
  */

int string_to_integer(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			/* Check for overflow */
			if (result > INT_MAX)
				return (-1);
		}
		else
			/* Non-numeric character encountered */
			return (-1);
	}
	return (result);
}

/**
  * integer_convert - Convert a long integer to a string
  * representation in a given base
  *
  * @value: The long integer to convert (long int)
  * @base: The base for conversion (int)
  * @flags: Flags for formatting (int)
  *
  * Return: A pointer to the string representation
  */

char *integer_convert(long int value, int base, int flags)
{
	static char *base_char;
	static char buffer[50];
	char sign = 0;
	char *result_ptr;
	unsigned long absolute_value = value < 0 ? -value : value;

	/* Check if the value is negative and set sign accordingly */
	if (!(flags & TO_UNSIGNED) && value < 0)
	{
		absolute_value = -value;
		sign = '-';

	}

	/* Set base characters based on the case (lowercase or uppercase) */
	base_char = (flags & TO_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	result_ptr = &buffer[49];
	*result_ptr = '\0';

	/* Convert the absolute value to the given base */
	do	{
		*--result_ptr = base_char[absolute_value % base];
		absolute_value = absolute_value / base;
	} while (absolute_value != 0);

	/* Add the sign if the value was negative */
	if (sign)
		*--result_ptr = sign;

	/* Return the pointer to the string representation */
	return (result_ptr);
}

/**
  * check_alphabetic - Check if a character is alphabetic
  *
  * @c: The character to check (int)
  *
  * Return: 1 if the character is alphabetic, 0 otherwise
  */

int check_alphabetic(int c)
{
	return (isalpha(c) != 0);
}
