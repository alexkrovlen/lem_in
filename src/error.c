/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:51:30 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:44:10 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			exit_error(void)
{
	ft_printf("ERROR\n");
	exit(0);
}

static void		free_used(t_anthill *anthill)
{
	free(anthill->used);
	free(anthill->parent);
	free(anthill->path_len);
}

static void		free_room(t_room *room)
{
	free(room->name);
	free(room);
}

void			free_anthill(t_anthill *anthill)
{
	int		i;
	t_room	*tmp;

	i = 0;
	if (anthill->room_list)
		free_ways(anthill);
	while (anthill->room_list)
	{
		tmp = anthill->room_list;
		anthill->room_list = anthill->room_list->next;
		free_room(tmp);
	}
	while (anthill->table_name != NULL && i < anthill->num_of_rooms)
	{
		free(anthill->table_links[i]);
		free(anthill->table_name[i]);
		i++;
	}
	free(anthill->table_links);
	free(anthill->table_name);
	if (anthill->used != NULL)
		free_used(anthill);
	free(anthill);
}

void			free_error(t_anthill *anthill, char *line)
{
	if (line != NULL)
		free(line);
	if (anthill->map != NULL)
		free_map(anthill);
	if (anthill != NULL)
		free_anthill(anthill);
	ft_printf("ERROR\n");
	exit(1);
}
