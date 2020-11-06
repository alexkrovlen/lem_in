/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:59:54 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 23:12:11 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static long long int	**init_res(t_anthill *anthill, \
						long long int **res, int max_len)
{
	long long int i;
	long long int j;

	i = 0;
	j = 0;
	while (i < anthill->num_ants)
	{
		j = 0;
		res[i] = (long long int *)ft_memalloc(sizeof(long long int) * \
				(anthill->num_ants * max_len));
		while (j < anthill->num_ants * max_len)
			res[i][j++] = -1;
		i++;
	}
	return (res);
}

static void				fill_res_help(t_way *head, long long int **res, int i)
{
	long long int count;
	long long int w;
	long long int j;

	count = 0;
	w = 0;
	j = 0;
	while (j < head->zero + head->size_way)
	{
		while (count++ < head->zero)
			j++;
		res[i][j] = head->way[w];
		w++;
		j++;
	}
}

static long long int	**fill_res(t_way *head, long long int **res)
{
	long long int	i;
	t_ant			*temp;

	while (head && head->size_ant > 0)
	{
		temp = head->struct_ant;
		while (temp)
		{
			i = 0;
			while (temp->num_ant - 1 != i)
				i++;
			fill_res_help(head, res, i);
			head->zero++;
			temp = temp->next;
		}
		head = head->next;
	}
	return (res);
}

static void				run_ants2(t_anthill *anthill)
{
	t_way			*head;
	t_ant			*tmp;
	long long int	ttt;

	head = anthill->head_ways;
	while (head)
	{
		ttt = 1;
		tmp = head->struct_ant;
		while (ttt < head->size_ant)
		{
			head->struct_ant->next = new_ant(anthill, head);
			if (head->struct_ant->next->num_ant == -1)
			{
				free_last_list(head->struct_ant);
				break ;
			}
			head->struct_ant = head->struct_ant->next;
			ttt++;
		}
		head->struct_ant = tmp;
		head = head->next;
	}
}

void					run_ants(t_anthill *anthill)
{
	long long int	**res;
	int				max_len;
	t_way			*head;

	res = (long long int **)ft_memalloc(sizeof(long long int *) * \
			anthill->num_ants);
	head = anthill->head_ways;
	while (head->next)
		head = head->next;
	max_len = head->size_way;
	init_res(anthill, res, max_len);
	head = anthill->head_ways;
	while (head)
	{
		head->struct_ant = init_struct_ant(head, anthill->num_ants);
		head = head->next;
	}
	head = anthill->head_ways;
	run_ants2(anthill);
	head = anthill->head_ways;
	size_ant(head);
	fill_res(head, res);
	print_ants(res, anthill, max_len);
	free_res(res, anthill->num_ants);
}
