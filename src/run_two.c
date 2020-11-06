/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:00:45 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 23:27:15 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		*find_num_ant_two(t_way *head, int *str)
{
	t_way	*h;
	int		i;

	i = 0;
	h = head;
	while (h->next)
	{
		str[i] = h->next->first_ant;
		i++;
		h = h->next;
	}
	str[i] = '\0';
	return (str);
}

static int		find_num_ant_three(t_way *head, t_anthill *anthill, int num_way)
{
	t_way	*h;

	h = anthill->head_ways;
	while (head->first_ant != h->first_ant)
	{
		num_way++;
		h = h->next;
	}
	return (num_way);
}

static t_ant	*find_last_ant(t_way *head)
{
	t_ant	*temp;

	temp = head->struct_ant;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

int				find_num_ant(t_anthill *anthill, t_way *head)
{
	int		num_ant;
	int		num_way;
	int		*str;
	int		i;
	t_ant	*temp;

	if (!(str = (int *)ft_memalloc(sizeof(int) * (anthill->num_of_ways))))
		return (-1);
	str = find_num_ant_two(head, str);
	i = 0;
	num_way = find_num_ant_three(head, anthill, 1);
	temp = find_last_ant(head);
	if (temp->num_ant + num_way >= str[i])
	{
		while (temp->num_ant + num_way >= str[i] && str[i] != '\0')
		{
			num_way++;
			i++;
		}
	}
	free(str);
	num_ant = temp->num_ant + num_way;
	if (num_ant > anthill->num_ants)
		return (-1);
	return (num_ant);
}

void			size_ant(t_way *head)
{
	t_way	*way;
	t_ant	*ant;
	int		count;

	way = head;
	while (head)
	{
		count = 0;
		ant = head->struct_ant;
		while (ant && ant->num_ant > 0)
		{
			ant = ant->next;
			count++;
		}
		head->size_ant = count;
		head = head->next;
	}
	head = way;
}
