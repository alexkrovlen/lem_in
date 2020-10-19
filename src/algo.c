# include "lem_in.h"

void 	algo(t_anthill *anthill)
{
	int *shortest_way;
	int *flag;
	int i;
	int j;
	int min;
	int m;

	i = 0;
	if (!(shortest_way = (int*)ft_memalloc(sizeof(int) * anthill->num_of_rooms))
		|| !(flag = (int*)ft_memalloc(sizeof(int) * anthill->num_of_rooms)))
		exit_error(); //free all
	while(i < anthill->num_of_rooms)
	{
		shortest_way[i] = 9999;
		flag[i] = 0;
	}
	shortest_way[anthill->start] = 0;
	//flag[anthill->start] = 1;
	i = 0;
	j = 0;
	while (m < 9999)
	{
		i = min_vertex;
		flag[anthill->start] = 1;
		j = 0;
		while (++j < anthill->num_of_rooms)
		{
			if (shortest_way[i] + anthill->table_links[i][j] < shortest_way[j])
			{
				shortest_way[j] = shortest_way[i] + anthill->table_links[i][j];
			}
		}
		m = 9999;
		j = 0;
		while (++j < anthill->num_of_rooms)
		{
			if (!flaf[j] && shortest_way[j] < m)
			{
				m = shortest_way[j];
				min_vertex = j;
			}
		}
	}
	




	/*while(i < anthill->num_of_rooms)
	{
		min = 9999;
		m = 0;
		while (m < anthill->num_of_rooms && flag[i] == 0 && i)
		{
			if (shortest_way[m] < min)
			{
				min = shortest_way[m];
				i = m;
			}
			m++;
		}
		while (j < anthill->num_of_rooms)
		{
			if (anthill->table_links[i][j] == 1)
				if (min + anthill->table_links[i][j] < shortest_way[i])
					shortest_way[i] = min + anthill->table_links[i][j];
			j++;
		}
		flag[i] = 1;
	}*/

	
}