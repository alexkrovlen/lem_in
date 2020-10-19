# include "lem_in.h"

void 				print_table(t_anthill *anthill)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_printf ("  | 0  1  2  3\n");
	ft_printf("________________\n");
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
