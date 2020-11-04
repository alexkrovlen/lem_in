/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:42:07 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/04 16:56:54 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					start_end_neighbor(t_anthill *anthill)
{
	int 	*tmp;

	tmp = anthill->table_links[anthill->start];
	if (tmp[anthill->end] == 1)
		return (1);
	return (0);
}

int					start_have_one_link(t_anthill *anthill)
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

void				init_for_alg(t_anthill *anthill)
{
	if (!(anthill->used = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms))\
		|| !(anthill->parent = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms))\
		|| !(anthill->path_len = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms)))
		exit_error (); //free all
	anthill->max_path_len = anthill->num_of_rooms + anthill->num_ants;
}

static void			bzero_for_alg(t_anthill *anthill)
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

static int			find_way(t_anthill *anthill)
{
	algo_bfs(anthill);
	if (!anthill->used[anthill->end])
		return (0);
	all_ways(anthill);
	return (1);
}

static t_anthill	*delete_rooms(t_anthill *anthill)
{
	int			i;
	int			j;

	i = anthill->parent[anthill->end];
	j = anthill->end;
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

static void			set_ants_to_ways(t_anthill *anthill)
{
	t_way	*head;
	int		size_way;
	int		diff;
	int		mod;
	int		first_ant_pr = 0;
	int		num_fr = 1;
	int		num_cur = 1;
	int		size_way_pr = 0;

	size_way = 0;
	head = anthill->head_ways;
	if (head == NULL)
		exit_error();
	while (head)
	{
		size_way = size_way + head->size_way;
		head = head->next;
	}
	mod = anthill->max_path_len % anthill->num_of_ways;
	head = anthill->head_ways;
	diff = (size_way + anthill->num_ants) / anthill->num_of_ways;
	while (head)
	{
		if (diff - head->size_way > 0)
			head->size_ant = diff - head->size_way;
		else
			head->size_ant = 0;
		if (head->first_ant == 1)
			head->first_ant = head->first_ant;
		else
			head->first_ant = (head->size_way - size_way_pr) * (num_cur - num_fr) + first_ant_pr + 1;
		first_ant_pr = head->first_ant;
		num_cur++;
		size_way_pr = head->size_way;
		head = head->next;
	}
}

static void			check_first_and_size(t_anthill *anthill)
{
	t_way *head;

	head = anthill->head_ways;
	while (head)
	{
		if (head->size_ant == 0)
			head->first_ant = 0;
		head = head->next;
	}
}

void				algo(t_anthill *anthill)
{
	int flag;

	flag = start_end_neighbor(anthill);
	if (flag == 1 && start_have_one_link(anthill))
		this_is_match(anthill);
	init_for_alg(anthill);
	bzero_for_alg(anthill);
	anthill->num_of_ways = 0;
	if (flag == 1)
	{
		anthill->parent[anthill->end] = anthill->start;
		anthill->path_len[anthill->end] = 1;
		all_ways(anthill);
		anthill->table_links[anthill->end][anthill->start] = 0;
		anthill->table_links[anthill->start][anthill->end] = 0;
		anthill->path_len[anthill->end] = -1;
		anthill->parent[anthill->end] = -1;
	}
	while (find_way(anthill))
	{
		anthill = delete_rooms(anthill);
	}
	set_ants_to_ways(anthill);
	check_first_and_size(anthill);
}
