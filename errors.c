
#include "my_shell.h"

int num_len(int num);
char *my_shell_itoa(int num);
int my_create_err(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
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
 * my_shell_itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *my_shell_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
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
 * my_create_err - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int my_create_err(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = my_err_env(args);
		break;
	case 1:
		error = my_err_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = my_err_2(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = my_err_4(args);
		else
			error = my_err_3(args);
		break;
	case 126:
		error = my_err_5(args);
		break;
	case 127:
		error = my_err_6(args);
		break;
	}
	write(STDERR_FILENO, error, my_strlen(error));

	if (error)
		free(error);
	return (err);

}
