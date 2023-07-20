#include "my_shell.h"

custom_alias_t *add_alias_end(custom_alias_t **head, char *name, char *value);
void free_alias_list(custom_alias_t *head);
dir_list_t *add_node_end(dir_list_t **head, char *path);
void free_list(dir_list_t *head);

/**
 * add_alias_end - Adds a node to the end of an custom_alias_t linked list.
 * @head: A pointer to the head of the custom_alias_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
custom_alias_t *add_alias_end(custom_alias_t **head, char *name, char *value)
{
	custom_alias_t *new_node = malloc(sizeof(custom_alias_t));
	custom_alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (get_string_length(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	copy_string(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Adds a node to the end of a dir_list_t linked list.
 * @head: A pointer to the head of the dir_list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
dir_list_t *add_node_end(dir_list_t **head, char *path)
{
	dir_list_t *new_node = malloc(sizeof(dir_list_t));
	dir_list_t *last;

	if (!new_node)
		return (NULL);

	new_node->path = path;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_alias_list - Frees an custom_alias_t linked list.
 * @head: The head of the custom_alias_t list.
 */
void free_alias_list(custom_alias_t *head)
{
	custom_alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a dir_list_t linked list.
 * @head: The head of the dir_list_t list.
 */
void free_list(dir_list_t *head)
{
	dir_list_t *next;

	while (head)
	{
		next = head->next;
		free(head->path);
		free(head);
		head = next;
	}
}
