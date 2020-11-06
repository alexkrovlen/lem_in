/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:13:33 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:22:47 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			start_end_neighbor(t_anthill *anthill)
{
	int		*tmp;

	tmp = anthill->table_links[anthill->start];
	if (tmp[anthill->end] == 1)
		return (1);
	return (0);
}

int			start_have_one_link(t_anthill *anthill)
{
	int		*tmp;
	int		i;
	int		sum;

	tmp = anthill->table_links[anthill->start];
	sum = 0;
	i = 0;
	while (i < anthill->num_of_rooms)
	{
		sum = sum + tmp[i];
		i++;
	}
	if (sum == 1)
		return (1);
	return (0);
}

void		init_for_alg(t_anthill *anthill)
{
	if (!(anthill->used = (int *)ft_memalloc(sizeof(int) * \
			anthill->num_of_rooms))\
		|| !(anthill->parent = (int *)ft_memalloc(sizeof(int) * \
			anthill->num_of_rooms))\
		|| !(anthill->path_len = (int *)ft_memalloc(sizeof(int) * \
			anthill->num_of_rooms)))
		free_error(anthill, NULL);
	anthill->max_path_len = anthill->num_of_rooms + anthill->num_ants;
}

t_anthill	*delete_rooms(t_anthill *anthill, int i, int j)
{
	while (anthill->used[anthill->start] != 0)
	{
		if (j == anthill->start || j == anthill->end)
		{
			anthill->used[j] = 0;
			anthill->path_len[j] = -1;
			j = i;
			i = anthill->parent[j];
		}
		else
		{
			anthill->used[j] = -1;
			j = i;
			i = anthill->parent[j];
		}
	}
	i = 0;
	while (i < anthill->num_of_rooms)
	{
		if (anthill->used[i] == 1)
			anthill->used[i] = 0;
		i++;
	}
	return (anthill);
}

void		bzero_for_alg(t_anthill *anthill)
{
	int i;

	i = 0;
	while (i < anthill->num_of_rooms)
	{
		anthill->used[i] = 0;
		anthill->path_len[i] = -1;
		anthill->parent[i] = -1;
		i++;
	}
}
