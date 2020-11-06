/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_three.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:02:24 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 23:03:28 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant		*new_ant(t_anthill *anthill, t_way *head)
{
	t_ant *list;

	if (!(list = (t_ant *)ft_memalloc(sizeof(t_ant))))
		return (NULL);
	list->num_ant = find_num_ant(anthill, head);
	list->next = NULL;
	return (list);
}

t_ant		*init_struct_ant(t_way *head, int num_ants)
{
	t_ant *struct_ant;

	if (!(struct_ant = (t_ant *)ft_memalloc(sizeof(t_ant))))
		return (NULL);
	if (head->first_ant > num_ants)
		struct_ant->num_ant = 0;
	else
		struct_ant->num_ant = head->first_ant;
	struct_ant->next = NULL;
	return (struct_ant);
}

void		free_last_list(t_ant *ant)
{
	t_ant *list;

	list = ant;
	while (ant->next->next)
	{
		ant = ant->next;
	}
	free(ant->next);
	ant->next = NULL;
	ant = list;
}
