/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:58:34 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/04 16:57:51 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		empty_queue(t_queue *q)
{
	return (q == NULL);
}

t_queue	*pop_queue(t_queue *q)
{
	t_queue *tmp;

	if (q == NULL)
		return (NULL);
	tmp = q->next;
	return (tmp);
}

t_queue	*new_queue(int n)
{
	t_queue *new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new->num = n;
	new->next = NULL;
	return (new);
}

t_queue	*push_queue(t_queue *queue, int n)
{
	t_queue *tmp;

	if (queue == NULL)
	{
		queue = new_queue(n);
		return (queue);
	}
	else
	{
		tmp = queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_queue(n);
		return (queue);
	}
}
