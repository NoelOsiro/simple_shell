#include "shell.h"

AliasNode *add_alias_end(AliasNode **head, char *name, char *value);
void free_alias_list(AliasNode *head);
ListNode *add_node_end(ListNode **head, char *dir);
void free_list(ListNode *head);

/**
 * add_alias_end - Adds a node to the end of an AliasNode linked list.
 * @head: A pointer to the head of the AliasNode list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
AliasNode *add_alias_end(AliasNode **head, char *name, char *value)
{
	AliasNode *new_node = malloc(sizeof(AliasNode));
	AliasNode *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

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
 * add_node_end - Adds a node to the end of a ListNode linked list.
 * @head: A pointer to the head of the ListNode list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
ListNode *add_node_end(ListNode **head, char *dir)
{
	ListNode *new_node = malloc(sizeof(ListNode));
	ListNode *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
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
 * free_alias_list - Frees an AliasNode linked list.
 * @head: The head of the AliasNode list.
 */
void free_alias_list(AliasNode *head)
{
	AliasNode *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a ListNode linked list.
 * @head: The head of the ListNode list.
 */
void free_list(ListNode *head)
{
	ListNode *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
