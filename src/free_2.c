/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:06:00 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:57:47 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_map	*free_m(t_map *m)
{
	t_map	*next;
	t_map	*prev;

	next = m->next;
	prev = m->prev;
	if (prev != NULL)
		prev->next = m->next;
	if (next != NULL)
		next->prev = m->prev;
	free(m->str);
	free(m);
	return (prev);
}

void			free_map(t_anthill *anthill)
{
	while (anthill->map)
	{
		anthill->map = free_m(anthill->map);
	}
	free(anthill->map);
}

void			free_res(long long int **res, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(res[i]);
		i++;
	}
	free(res);
}
