/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:53:11 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/05 20:32:37 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_anthill	*anthill;

	anthill = init_anthill();
	parse(anthill);
	algo(anthill);
	print_map(anthill);
	run_ants(anthill);
	free_all(anthill);
	return (0);
}
