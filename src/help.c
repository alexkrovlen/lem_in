/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:52:40 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/04 16:52:27 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_space(char *ch)
{
	if (*ch == ' ' || *ch == '\n' || *ch == '\t' || *ch == '\v' ||
		*ch == '\f' || *ch == '\r')
		return (1);
	return (0);
}

int				ft_atoi_new(char *str)
{
	int			i;
	long int	res;
	int			flag;

	flag = 1;
	res = 0;
	i = 0;
	while (str[i] && ft_space(&str[i]))
		i++;
	if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		i++;
		flag = -1;
	}
	else if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res * 10 + (str[i] - '0') < res)
			return (-1);
		res = 10 * res + (str[i++] - '0');
	}
	if (res * flag > INT32_MAX || res * flag < INT32_MIN)
		return (-1);
	return (res * flag);
}
