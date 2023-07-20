#include "my_shell.h"

int calculate_num_length(int num);
char *convert_int_to_string(int num);
int display_custom_error(char **args, int err);

/**
 * calculate_num_length - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int calculate_num_length(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * convert_int_to_string - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *convert_int_to_string(int num)
{
	char *buffer;
	int len = calculate_num_length(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * display_custom_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int display_custom_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_message_env(args);
		break;
	case 1:
		error = error_message_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_message_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_message_2_syntax(args);
		else
			error = error_message_2_cd(args);
		break;
	case 126:
		error = error_message_126(args);
		break;
	case 127:
		error = error_message_127(args);
		break;
	default:
		error = NULL;
	}

	write(STDERR_FILENO, error, get_string_length(error));

	if (error)
		free(error);
	return (err);
}
