/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:58:47 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:56:22 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_coord(t_anthill *anthill, t_room *room)
{
	t_room *tmp;

	tmp = anthill->room_list;
	while (tmp)
	{
		if (tmp->coord_x == room->coord_x && tmp->coord_y == room->coord_y)
			if (tmp->status != 1 && tmp->status != 2)
				free_error(anthill, NULL);
		tmp = tmp->next;
	}
}

void	room_add(t_anthill *anthill, t_room *room)
{
	if (room == NULL)
		return ;
	check_coord(anthill, room);
	if (anthill->room_list == NULL)
	{
		anthill->room_list = room;
	}
	else
	{
		room->next = anthill->room_list;
		anthill->room_list = room;
	}
}

t_room	*room_new(char *name, int x, int y, int status)
{
	t_room	*room;

	if (!(room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(name);
	room->coord_x = x;
	room->coord_y = y;
	room->status = status;
	room->next = NULL;
	return (room);
}
