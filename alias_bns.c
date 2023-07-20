#include "my_shell.h"
int my_shell_alias(char **args, char __attribute__((__unused__)) **front);
void set_custom_alias(char *alias_name, char *value);
void print_custom_alias(custom_alias_t *alias);

/**
 * my_shell_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_shell_alias(char **args, char __attribute__((__unused__)) **front)
{
	custom_alias_t *temp = custom_aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_custom_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = custom_aliases;
		value = find_character(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (compare_strings(args[i], temp->name) == 0)
				{
					print_custom_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error_message(args + i, 1);
		}
		else
			set_custom_alias(args[i], value);
	}
	return (ret);
}

/**
 * set_custom_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @alias_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_custom_alias(char *alias_name, char *value)
{
	custom_alias_t *temp = custom_aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = get_string_length(value) - find_string_length_in_set(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (compare_strings(alias_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias(&custom_aliases, alias_name, new_value);
}

/**
 * print_custom_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_custom_alias(custom_alias_t *alias)
{
	char *alias_string;
	int len = get_string_length(alias->name) + get_string_length(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	copy_string(alias_string, alias->name);
	concatenate_strings(alias_string, "='");
	concatenate_strings(alias_string, alias->value);
	concatenate_strings(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_custom_aliases - Goes through the arguments and replaces any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_custom_aliases(char **args)
{
	custom_alias_t *temp;
	int i;
	char *new_value;

	if (compare_strings(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = custom_aliases;
		while (temp)
		{
			if (compare_strings(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (get_string_length(temp->value) + 1));
				if (!new_value)
				{
					free_arguments(args, args);
					return (NULL);
				}
				copy_string(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
