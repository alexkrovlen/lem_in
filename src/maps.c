/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:53:25 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/04 14:53:26 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		*head = map_create(str);
	else
	{
		new = (*head);
		(*head)->next = map_create(str);
		(*head) = (*head)->next;
		(*head)->prev = new;
	}
}
