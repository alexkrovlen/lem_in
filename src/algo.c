# include "lem_in.h"

int 	start_end_neighbor(t_anthill *anthill)
{
	int 	*tmp;

	tmp = anthill->table_links[anthill->start];
	if (tmp[anthill->end] == 1)
		return (1);
	return (0);
}

int start_have_one_link(t_anthill *anthill)
{
	int		*tmp;
	int		i;
	int		sum;

	tmp = anthill->table_links[anthill->start];
	sum = 0;
	i = 0;
	while(i < anthill->num_of_rooms)
	{
		sum = sum + tmp[i];
		i++;
	}
	if (sum == 1)
		return (1);
	return (0);
}

void init_for_alg(t_anthill *anthill)
{
	if (!(anthill->used = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms))\
		|| !(anthill->parent = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms))\
		|| !(anthill->path_len = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms)))
		exit_error (); //free all
	anthill->max_path_len = anthill->num_of_rooms + anthill->num_ants;
}

static void	bzero_for_alg(t_anthill *anthill)
{
	int i;

	i = 0;
	while (i < anthill->num_of_rooms)
	{
		anthill->used[i] = 0;
		anthill->path_len[i] = -1;
		anthill->parent[i] = -1;
		i++;
	}
}

static int find_way(t_anthill *anthill)
{
	algo_bfs(anthill);
	/*printf("neighbor \n");
	int i = 0;
	while (i < anthill->num_of_rooms)
	{
		printf("used = %d parent = %d path_len = %d\n", anthill->used[i], anthill->parent[i], anthill->path_len[i]);
		i++;
	}
	*/
	if (!anthill->used[anthill->end] /*|| anthill->max_path_len - anthill->path_len[anthill->end] < 2*/)
	{
		printf("oki moki\n");
		return (0);
	}
	all_ways(anthill);
	/*printf("\nALL WAYS\n");
	int b = 0;
	while (b < anthill->num_of_rooms)
	{
		printf("used = %d parent = %d path_len = %d\n", anthill->used[b], anthill->parent[b], anthill->path_len[b]);
		b++;
	}*/
	return (1);
}

static t_anthill		*delete_rooms(t_anthill *anthill)
{
	int			i;
	int			j;

	i = anthill->parent[anthill->end];
	j = anthill->end;
	/*printf("neighbor \n");
	int b = 0;
	while (b < anthill->num_of_rooms)
	{
		printf("used = %d parent = %d path_len = %d\n", anthill->used[b], anthill->parent[b], anthill->path_len[b]);
		b++;
	}
	getchar();*/
	//while (i != anthill->start)
	while (anthill->used[anthill->start] != 0)
	{//printf("!\n");
		if (j == anthill->start || j == anthill->end)
		{
			anthill->used[j] = 0;
			anthill->path_len[j] = -1;
			j = i;
			i = anthill->parent[j];
		}
		else //if (anthill->table_links[i][j] == 1)
		{
			anthill->used[j] = -1;
			j = i;
			i = anthill->parent[j];
		}
	}
	/*printf("!!!!!!!!!!!!!!!!\n");
	b = 0;
	while (b < anthill->num_of_rooms)
	{
		printf("used = %d parent = %d path_len = %d\n", anthill->used[b], anthill->parent[b], anthill->path_len[b]);
		b++;
	}
	getchar();*/
	i = 0;
	while (i < anthill->num_of_rooms)
	{
		if (anthill->used[i] == 1)
			anthill->used[i] = 0;
		i++;
	}
/*
	printf("\nPOSLE DELETE\n");
	int b = 0;
	while (b < anthill->num_of_rooms)
	{
		printf("used = %d parent = %d path_len = %d\n", anthill->used[b], anthill->parent[b], anthill->path_len[b]);
		b++;
	}
	getchar();*/
	return (anthill);
}

void 	algo(t_anthill *anthill)
{
	if (start_end_neighbor(anthill) && start_have_one_link(anthill))
		this_is_match(anthill);
	init_for_alg(anthill);
	bzero_for_alg(anthill);
	anthill->num_of_ways = 0;
	while (find_way(anthill))
	{
		anthill = delete_rooms(anthill);
		//bzero_for_alg(anthill);
	}
}