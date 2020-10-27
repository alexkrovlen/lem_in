# include "lem_in.h"

t_queue		*find_id_room(t_anthill *anthill, t_queue *queue, int id)
{
	//int *neighbor;
	int j;

	j = 0;
	while (j < anthill->num_of_rooms)
	{
		if (anthill->used[j] != -1 && anthill->table_links[id][j] == 1)
		{//printf("3\n");
			queue = push_queue(queue, j);
			if (j != anthill->end)
			{
				anthill->parent[j] = id;
				anthill->path_len[j] = anthill->path_len[id] + 1;
				anthill->used[j] = 1;
				anthill->table_links[j][id] = 0;
			}
			else if (j == anthill->end && anthill->path_len[j] > anthill->path_len[id] + 1)
			{
				anthill->parent[j] = id;
				anthill->path_len[j] = anthill->path_len[id] + 1;
				anthill->used[j] = 1;
				anthill->table_links[j][id] = 0;
			}
			else if (j == anthill->end && anthill->path_len[j] == -1)
			{
				anthill->parent[j] = id;
				anthill->path_len[j] = anthill->path_len[id] + 1;
				anthill->used[j] = 1;
				anthill->table_links[j][id] = 0;
			}
		}
		j++;
	}
	return (queue);
}
		
void		algo_bfs(t_anthill *anthill)
{
	t_queue *queue;
	int		id_room;

	queue = NULL;
	queue = push_queue(queue, anthill->start);
	anthill->path_len[anthill->start] = 0;
	anthill->used[anthill->start] = 1;
	/*printf("\n\nALGO    BFS!!!!!!!!!\n\n");
	int i = 0;
	while (i < anthill->num_of_rooms)
	{
		printf("used = %d parent = %d path_len = %d\n", anthill->used[i], anthill->parent[i], anthill->path_len[i]);
		i++;
	}*/
	while (!empty_queue(queue))
	{
		id_room = queue->num; 
		queue = pop_queue(queue);
		if (id_room == anthill->end)
			continue ;
		queue = find_id_room(anthill, queue, id_room);
	}
	while (!empty_queue(queue))
	{
		queue = pop_queue(queue);
	}
	/*printf("\n\nPOSLE BFS\n\n");
	i = 0;
	while (i < anthill->num_of_rooms)
	{
		printf("used = %d parent = %d path_len = %d\n", anthill->used[i], anthill->parent[i], anthill->path_len[i]);
		i++;
	}*/
}
