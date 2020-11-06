/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:51:29 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:53:45 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_room(char *str)
{
	char	**array;

	if (ft_word_count(str, ' ') != 3)
		return (0);
	array = ft_strsplit(str, ' ');
	if (array[0][0] == 'L' || ft_isdigit(ft_atoi_new(array[1])) == 0 \
		|| ft_isdigit(ft_atoi_new(array[2])) == 0)
	{
		ft_free_split(array, 3);
		return (0);
	}
	ft_free_split(array, 3);
	return (1);
}

void		detect_room(t_anthill *anthill, char *line, int *status)
{
	char	**array;
	int		x;
	int		y;

	array = ft_strsplit(line, ' ');
	if (*status == 3)
		*status = 0;
	x = ft_atoi_new(array[1]);
	y = ft_atoi_new(array[2]);
	if (x == -1 || y == -1)
		free_error(anthill, NULL);
	room_add(anthill, room_new(array[0], x, y, *status));
	if (*status == 1 && anthill->start == -1)
		anthill->start = anthill->num_of_rooms;
	else if (*status == 2 && anthill->end == -1)
		anthill->end = anthill->num_of_rooms;
	*status = 0;
	anthill->num_of_rooms++;
	ft_free_split(array, 3);
	return ;
}

void		check_name_room(t_anthill *anthill, char *str1, char *str2)
{
	t_room	*room;
	int		res;

	room = anthill->room_list;
	res = 0;
	while (room)
	{
		if (ft_strequ(room->name, str1) || ft_strequ(room->name, str2))
			res++;
		room = room->next;
	}
	if (res != 2)
		free_error(anthill, NULL);
}
