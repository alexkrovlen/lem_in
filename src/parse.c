/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:56:22 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:56:02 by fjessi           ###   ########.fr       */
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
			free_error(anthill, line);
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
	else if (str[0] == '#' && str[1] == '#' && \
	(ft_strcmp(str, "##start") && ft_strcmp(str, "##end")))
		return (IGNOR);
	else
		return (0);
}

static void	get_links_help(t_anthill *anthill, char *line)
{
	links_add(anthill, line);
	map_add(&(anthill->map), ft_strdup(line));
	free(line);
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
			get_links_help(anthill, line);
		else
			free_error(anthill, line);
	}
}

void		parse(t_anthill *anthill)
{
	if ((anthill->num_ants = count_of_ants(anthill)) <= 0)
		free_error(anthill, NULL);
	check_rooms(anthill);
	if (anthill->table_links == NULL || anthill->room_list == NULL)
		free_error(anthill, NULL);
}
