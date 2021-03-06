/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojoseph <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:01:57 by jojoseph          #+#    #+#             */
/*   Updated: 2020/02/14 22:01:59 by jojoseph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ftoa(double nbr, unsigned int precision)
{
	return (ft_ftoa_long(nbr, precision));
}
