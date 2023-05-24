#include "main.h"

/**
 * free_sep_list - frees a list
 * @head: pointer.
 * Return: void.
 */

void free_sep_list(sep_list **head)
{
	sep_list *tmp;
	sep_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}