# include "lem_in.h"

static t_map	*map_create(char *str)
{
	t_map	*current;

	current = malloc(sizeof(t_map));
	if (current)
	{
		current->str = str;
		current->next = NULL;
		current->prev = NULL;
	}
	return (current);
}

void			map_add(t_map **head, char *str)
{
	t_map	*new;

	if (!(*head))
		*head = ft_map_create(str);
	else
	{
		new = (*head);
		(*head)->next = ft_map_create(str);
		(*head) = (*head)->next;
		(*head)->prev = new;
	}
}