#include "main.h"

/**
 * free_line_list - frees a line
 * @head: pointer.
 * Return: no return.
 */

void free_line_list(line_list **head)
{
	line_list *tmp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((tmp = curr) != NULL)
		{
			curr = curr->next;
			free(tmp);
		}
		*head = NULL;
	}
}
