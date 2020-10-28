# include "lem_in.h"

void 				print_table(t_anthill *anthill)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_printf ("  | 0  1  2  3  4  5  6  7  8  9  10 11 12\n");
	ft_printf("_________________________________________\n");
	while ( i < anthill->num_of_rooms)
	{
		j= 0;
		ft_printf ("%d | ", i);
		while (j < anthill->num_of_rooms)
		{
			ft_printf("%d  ", anthill->table_links[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void 				print_map(t_anthill *anthill)
{
	t_map *map;

	map = anthill->map;
	while(map->prev)
		map = map->prev;
	while (map)
	{
		ft_printf("%s\n", map->str);
		map = map->next;
	}
	ft_printf("\n");
}

void	this_is_match(t_anthill *anthill)
{
	int i;

	i = 1;
	while (i <= anthill->num_ants)
	{
		ft_printf("L%d-%s ", i, anthill->table_name[anthill->end]);
		i++;
	}
	ft_printf("\n");
	exit (0);
}

void				print_ants(int **res, t_anthill *anthill, int max_len)
{
	int i;
	int j;
	int flag;

	j = 0;
	
	while (j < anthill->num_ants * max_len)
	{
		i = 0;
		flag = 0;
		while (i < anthill->num_ants)
		{//printf("res = %d\n", res[i][j]);
			if (res[i][j] != -1)
				printf("L%d-%s ", i+1, anthill->table_name[res[i][j]]);
			else
				flag++;			
			i++;
		}
		if (flag != anthill->num_ants)
			printf("\n");
		else
			break ;
		j++;
	}
	
}
