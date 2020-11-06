/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:51:59 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:44:54 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_split(char **str, int j)
{
	while (--j != -1)
		free(str[j]);
	free(str);
}

void	free_ant(t_way *w)
{
	t_ant	*a;

	while (w->struct_ant)
	{
		a = w->struct_ant;
		w->struct_ant = w->struct_ant->next;
		free(a);
	}
}

void	free_way(t_way *way)
{
	free_ant(way);
	free(way->way);
	free(way);
}

void	free_ways(t_anthill *anthill)
{
	t_way *way;

	while (anthill->head_ways)
	{
		way = anthill->head_ways;
		anthill->head_ways = anthill->head_ways->next;
		free_way(way);
	}
}

void	free_all(t_anthill *anthill)
{
	if (anthill->map != NULL)
		free_map(anthill);
	if (anthill != NULL)
		free_anthill(anthill);
}
