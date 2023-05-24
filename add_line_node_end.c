#include "main.h"
/**
 * add_line_node_end - place  cmd line in the end
 * @head: pointer.
 * @line: line.
 * Return: pointer.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *tmp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}
