/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:54:01 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:55:16 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		create_table_links2(t_anthill *anthill, t_room *room)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (count < anthill->num_of_rooms)
	{
		if (!(anthill->table_links[count] = (int *)ft_memalloc(sizeof(int)\
		* anthill->num_of_rooms)))
			return (1);
		else
		{
			while (i < anthill->num_of_rooms)
			{
				anthill->table_links[count][i] = 0;
				i++;
			}
		}
		anthill->table_name[count] = ft_strdup(room->name);
		room = room->next;
		count++;
	}
	return (0);
}

int		create_table_links(t_anthill *anthill)
{
	t_room	*room;

	room = anthill->room_list;
	if (!(anthill->table_links = (int **)ft_memalloc(sizeof(int *)\
	* anthill->num_of_rooms)))
		return (1);
	if (!(anthill->table_name = (char **)ft_memalloc(sizeof(char *)\
	* anthill->num_of_rooms)))
		return (1);
	if (!create_table_links2(anthill, room))
	{
		anthill->start = anthill->num_of_rooms - anthill->start - 1;
		anthill->end = anthill->num_of_rooms - anthill->end - 1;
	}
	else
		return (1);
	return (0);
}

void	links_add(t_anthill *anthill, char *line)
{
	char	**str;
	int		first;
	int		second;
	int		num;

	if (anthill->table_links == NULL && anthill->table_name == NULL)
	{
		if (create_table_links(anthill))
			free_error(anthill, line);
	}
	str = ft_strsplit(line, '-');
	check_name_room(anthill, str[0], str[1]);
	num = anthill->num_of_rooms - 1;
	while (num >= 0)
	{
		if (ft_strequ(anthill->table_name[num], str[0]))
			first = num;
		if (ft_strequ(anthill->table_name[num], str[1]))
			second = num;
		num--;
	}
	anthill->table_links[first][second] = 1;
	anthill->table_links[second][first] = 1;
	ft_free_split(str, 2);
}

int		is_links(char *str)
{
	if (ft_strchr(str, '-') == NULL)
		return (0);
	return (1);
}
