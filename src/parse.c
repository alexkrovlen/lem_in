/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:56:22 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/04 20:11:54 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	count_of_ants(t_anthill *anthill)
{
	char	*line;
	int		res;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
			continue ;
		}
		else if (ft_strchr(line, ' ') != NULL || (ft_atoi_new(line)) <= 0)
		{
			free(line);
			exit_error();
		}
		else
		{
			map_add(&(anthill->map), ft_strdup(line));
			res = ft_atoi_new(line);
			free(line);
			return (res);
		}
	}
	return (0);
}

int			is_hash(char *str, t_anthill *anthill)
{
	if ((!ft_strcmp(str, "##start")) && anthill->start == -1)
		return (START);
	else if ((!ft_strcmp(str, "##end")) && anthill->end == -1)
		return (END);
	else if (str[0] == '#' && str[1] != '#')
		return (COMMENT);
	else if (str[0] == '#' && str[1] == '#' && (ft_strcmp(str, "##start") && ft_strcmp(str, "##end")))
		return (IGNOR);
	else
		return (0);
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
		exit_error();
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

int			is_room(char *str)
{
	char	**array;

	if (ft_word_count(str, ' ') != 3)
		return (0);
	array = ft_strsplit(str, ' ');
	if (array[0][0] == 'L' || ft_isdigit(ft_atoi_new(array[1])) == 0 || ft_isdigit(ft_atoi_new(array[2])) == 0)
	{
		ft_free_split(array, 3);
		exit_error();
	}
	ft_free_split(array, 3);
	return (1);
}

int			is_links(char *str)
{
	if (ft_strchr(str, '-') == NULL)
		return (0);
	return (1);
}

int			create_table_links(t_anthill *anthill)
{
	int		count;
	t_room	*room;
	int		i;

	count = 0;
	room = anthill->room_list;
	if (!(anthill->table_links = (int **)ft_memalloc(sizeof(int *) * anthill->num_of_rooms)))
		return (1);
	if (!(anthill->table_name = (char **)ft_memalloc(sizeof(char *) * anthill->num_of_rooms)))
		return (1);
	while (count < anthill->num_of_rooms)
	{
		i = 0;
		if (!(anthill->table_links[count] = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms)))
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
	anthill->start = anthill->num_of_rooms - anthill->start - 1;
	anthill->end = anthill->num_of_rooms - anthill->end - 1;
	return (0);
}

static void	check_name_room(t_anthill *anthill, char *str1, char *str2)
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
		exit_error(); //free all
}

void		links_add(t_anthill *anthill, char *line)
{
	char	**str;
	int		first;
	int		second;
	int		num;

	if (anthill->table_links == NULL && anthill->table_name == NULL)
	{
		if (create_table_links(anthill))
			exit_error(); //free all
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
}

static void	check_rooms(t_anthill *anthill)
{
	char	*line;
	int		status;

	status = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (is_hash(line, anthill) != 0)
		{
			status = is_hash(line, anthill);
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else if (is_room(line) && anthill->table_links == NULL)
		{
			detect_room(anthill, line, &status);
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else if (is_links(line) && anthill->start != -1 && anthill->end != -1)
		{
			links_add(anthill, line);
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else
		{
			exit_error();
			//free all
		}
	}
}

void		parse(t_anthill *anthill)
{
	if ((anthill->num_ants = count_of_ants(anthill)) <= 0)
		exit_error();
	check_rooms(anthill);
	if (anthill->table_links == NULL || anthill->room_list == NULL)
		exit_error();
}
