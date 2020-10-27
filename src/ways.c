# include "lem_in.h"

static t_way *new_way(t_anthill *anthill)
{
	t_way *new;
	int len;
	int i;
	int id_room;

	if (!(new = (t_way *)ft_memalloc(sizeof(t_way))))
		exit_error (); //free all
	len = anthill->path_len[anthill->end];
	if (!(new->way = (int *)ft_memalloc(sizeof(int) * len)))
		exit_error (); //free all
	new->size_ant = 0;
	new->size_way = len;
	new->first_ant = 0;
	new->zero = 0;
	new->next = NULL;
	id_room = anthill->end;
	i = 0;
	while(i < len)
	{
		new->way[len - i - 1] = id_room;
		id_room = anthill->parent[id_room];
		i++;
	}
	//printf ("id_room = %d\n", id_room);
	//printf ("anthill->start = %d\n", anthill->start);
	/*if (id_room != anthill->start)
		exit_error ();*/
	
	return (new);
}

static void use_way(t_anthill *anthill, t_way *way)
{
	t_way	*tmp;

	if (!anthill->head_ways)
	{
		anthill->head_ways = way;
		anthill->head_ways->size_ant = 0;
		anthill->head_ways->first_ant = 1;
		anthill->head_ways->zero = 0;
		//set_ants_to_ways(anthill, way->size_way);
	}
	else
	{
		tmp = anthill->head_ways;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = way;
		//set_ants_to_ways(anthill, way->size_way);
	}
}

void		all_ways(t_anthill *anthill)
{
	t_way *way;

	way = NULL;
	anthill->num_of_ways++;
	way = new_way(anthill);
	use_way(anthill, way);
}
