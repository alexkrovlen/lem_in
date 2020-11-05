/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:59:54 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/05 20:26:42 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			find_num_ant(t_anthill *anthill, t_way *head)
{
	int		num_ant;
	int		num_way;
	t_way	*h;
	int		*str;
	int		i;

	i = 0;
	h = head;
	if (!(str = (int *)ft_memalloc(sizeof(int) * (anthill->num_of_ways - 1))))
		return (-1);
	while (h->next)
	{
		str[i] = h->next->first_ant;
		i++;
		h = h->next;
	}
	str[i] = '\0';
	i = 0;
	num_ant = head->first_ant;
	num_way = 1;
	h = anthill->head_ways;
	while (head->first_ant != h->first_ant)
	{
		num_way++;
		h = h->next;
	}
	while (head->struct_ant->next)
		head->struct_ant = head->struct_ant->next;
	if (head->struct_ant->num_ant + num_way >= str[i])
	{
		while (head->struct_ant->num_ant + num_way >= str[i] && str[i] != '\0')
		{
			num_way++;
			i++;
		}
	}
	free(str);
	num_ant = head->struct_ant->num_ant + num_way;
	if (num_ant > anthill->num_ants)
		return (-1);
	return (num_ant);
}

static t_ant		*new_ant(t_anthill *anthill, t_way *head)
{
	t_ant *list;

	if (!(list = (t_ant *)ft_memalloc(sizeof(t_ant))))
		return (NULL);
	list->num_ant = find_num_ant(anthill, head);
	list->next = NULL;
	return (list);
}

static t_ant		*init_struct_ant(t_way *head, int num_ants)
{
	t_ant *struct_ant;

	if (!(struct_ant = (t_ant *)ft_memalloc(sizeof(t_ant))))
		return (NULL);
	if (head->first_ant > num_ants)
		struct_ant->num_ant = 0;
	else
		struct_ant->num_ant = head->first_ant;
	struct_ant->next = NULL;
	return (struct_ant);
}

static void			free_last_list(t_ant *ant)
{
	t_ant *list;

	list = ant;
	while (ant->next->next)
	{
		ant = ant->next;
	}
	free(ant->next);
	ant->next = NULL;
	ant = list;
}

static void			size_ant(t_way *head)
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

void				run_ants(t_anthill *anthill)
{
	long long int **res;
	long long int i;
	long long int j;
	int max_len;
	t_way *head;

	res = (long long int **)ft_memalloc(sizeof(long long int *) * anthill->num_ants);
	i = 0;
	j = 0;
	head = anthill->head_ways;
	while (head->next)
		head = head->next;
	max_len = head->size_way;
	while (i < anthill->num_ants)
	{
		j = 0;
		res[i] = (long long int *)ft_memalloc(sizeof(long long int) * (anthill->num_ants * max_len));
		while (j < anthill->num_ants * max_len)
			res[i][j++] = -1;
		i++;
	}
	i = 0;
	long long int count;
	long long int w;
	head = anthill->head_ways;
	while (head)
	{
		head->struct_ant = init_struct_ant(head, anthill->num_ants);
		head = head->next;
	}
	head = anthill->head_ways;
	long long int ttt = 1;
	t_ant *tmp;
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
	head = anthill->head_ways;
	size_ant(head);
	while (head && head->size_ant > 0)
	{
		while (head->struct_ant)
		{
			i = 0;
			w = 0;
			count = 0;
			j = 0;
			while (head->struct_ant->num_ant - 1 != i)
				i++;
			while (j < head->zero + head->size_way)
			{
				while (count++ < head->zero)
					j++;
				res[i][j] = head->way[w];
				w++;
				j++;
			}
			head->zero++;
			head->struct_ant = head->struct_ant->next;
		}
		head = head->next;
	}
	//print_way(res, anthill, max_len);
	print_ants(res, anthill, max_len);
	free_res(res, anthill->num_ants);
}

void				print_way(long long int **res, t_anthill *anthill, int max_len)
{
	long long int i;
	long long int j;

	i = 0;
	j = 0;
	ft_printf("_________________________________________\n");
	while (i < anthill->num_ants)
	{
		j = 0;
		ft_printf("%d | ", i);
		while (j < anthill->num_ants * max_len)
		{
			ft_printf("%d  ", res[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
