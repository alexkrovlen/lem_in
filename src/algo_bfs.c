# include "lem_in.h"

t_queue		*find_id_room(t_anthill *anthill, t_queue *queue, int id)
{
	//int *neighbor;
	int j;

//	neighbor = anthill->table_links[id];
	j = 0;
	while (j < anthill->num_of_rooms)
	{//printf("2\n");
	//printf("j = %d\n", j);
		if (/*anthill->used[j] == 0 && */anthill->table_links[id][j] == 1)
		{//printf("3\n");
			queue = push_queue(queue, j);
			anthill->parent[j] = id;
			anthill->path_len[j] = anthill->path_len[id] + 1;
			anthill->used[j] = 1;
			anthill->table_links[j][id] = 0;
		}
		j++;
	}
	return (queue);
}

void		algo_bfs(t_anthill *anthill)
{
	t_queue *queue;
	int		id_room;

	//queue = (t_queue *)ft_memalloc(sizeof(t_queue));
	queue = NULL;
	queue = push_queue(queue, anthill->start);
	//printf("num1 = %d\n", queue->num);
	//getchar ();
	anthill->path_len[anthill->start] = 0;
	anthill->used[anthill->start] = 1;
	while (!empty_queue(queue))
	{//printf("11111111\n");
	//getchar();
		id_room = queue->num;
		queue = pop_queue(queue);
		if (id_room == anthill->end)
			break ;
		queue = find_id_room(anthill, queue, id_room);
		//printf("num que = %d\n", queue->num);
	}
	while (!empty_queue(queue))
		pop_queue(queue);
}
