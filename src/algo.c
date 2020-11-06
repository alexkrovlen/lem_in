/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:42:07 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:24:32 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			get_head_size_ant(t_way *head, int diff, int mod)
{
	if (diff - head->size_way >= 0)
	{
		head->size_ant = mod > 0 ? diff - head->size_way + 1 : \
				diff - head->size_way;
		mod = mod > 0 ? mod - 1 : mod;
	}
	else
		head->size_ant = 0;
}

static void			set_ants_to_ways_two(t_way *head, int diff, int mod, \
														int first_ant_pr)
{
	int		size_way_pr;
	int		num_fr;
	int		num_cur;

	size_way_pr = 0;
	num_fr = 1;
	num_cur = 1;
	while (head)
	{
		get_head_size_ant(head, diff, mod);
		if (head->first_ant == 1)
			head->first_ant = head->first_ant;
		else
			head->first_ant = (head->size_way - size_way_pr) * \
				(num_cur - num_fr) + first_ant_pr + 1;
		first_ant_pr = head->first_ant;
		num_cur++;
		size_way_pr = head->size_way;
		head = head->next;
	}
}

static void			set_ants_to_ways(t_anthill *anthill)
{
	t_way	*head;
	int		size_way;
	int		diff;
	int		mod;
	int		first_ant_pr;

	first_ant_pr = 0;
	size_way = 0;
	head = anthill->head_ways;
	if (head == NULL)
		free_error(anthill, NULL);
	while (head)
	{
		size_way = size_way + head->size_way;
		head = head->next;
	}
	head = anthill->head_ways;
	diff = (size_way + anthill->num_ants) / anthill->num_of_ways;
	mod = (size_way + anthill->num_ants) % anthill->num_of_ways;
	set_ants_to_ways_two(head, diff, mod, first_ant_pr);
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
		anthill = delete_rooms(anthill, anthill->parent[anthill->end], \
														anthill->end);
	set_ants_to_ways(anthill);
	check_first_and_size(anthill);
}
