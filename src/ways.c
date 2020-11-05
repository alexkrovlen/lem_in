/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:02:32 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/05 19:16:15 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_way	*new_way(t_anthill *anthill)
{
	t_way	*new;
	int		len;
	int		i;
	int		id_room;

	if (!(new = (t_way *)ft_memalloc(sizeof(t_way))))
		free_error(anthill, NULL); //free all
	len = anthill->path_len[anthill->end];
	if (!(new->way = (int *)ft_memalloc(sizeof(int) * len)))
		free_error(anthill, NULL); //free all
	new->size_ant = 0;
	new->size_way = len;
	new->first_ant = 0;
	new->zero = 0;
	new->next = NULL;
	id_room = anthill->end;
	i = 0;
	while (i < len)
	{
		new->way[len - i - 1] = id_room;
		id_room = anthill->parent[id_room];
		i++;
	}
	return (new);
}

static void		use_way(t_anthill *anthill, t_way *way)
{
	t_way	*tmp;

	if (!anthill->head_ways)
	{
		anthill->head_ways = way;
		anthill->head_ways->size_ant = 0;
		anthill->head_ways->first_ant = 1;
		anthill->head_ways->zero = 0;
	}
	else
	{
		tmp = anthill->head_ways;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = way;
	}
}

void			all_ways(t_anthill *anthill)
{
	t_way *way;

	way = NULL;
	anthill->num_of_ways++;
	way = new_way(anthill);
	use_way(anthill, way);
}
