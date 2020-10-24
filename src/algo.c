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

static void set_ants_to_ways(t_anthill *anthill)
{
	t_way *h;
	h = anthill->head_ways;
	while (h)
	{
	printf ("anthill->num_of_ways = %d\n", anthill->num_of_ways);
	printf (" head->size_ant = %d\n", h->size_ant);
		printf ("\nh->first_ant = %d\n", h->first_ant);
	//printf("max_size_way = %d\n", max_size_way);
	printf("anthill->max_path_len = %d\n", anthill->max_path_len);
	printf(" anthill->head_ways->size_way = %d\n\n", h->size_way);
	printf("anthill->num_of_rooms = %d\n", anthill->num_of_rooms);
	h = h->next;
	}
	printf("11111111111111\n\n");
	t_way *head;
	int size_way;
	int diff;
	int mod;

	size_way = 0;
	head = anthill->head_ways;
	while (head)
	{
		size_way = size_way + head->size_way;
		head = head->next;
	}
	anthill->max_path_len = size_way + anthill->num_ants;
	diff = anthill->max_path_len / anthill->num_of_ways;
	mod = anthill->max_path_len % anthill->num_of_ways;
	printf ("\ndiff = %d\n", diff);
	printf ("mod = %d\n\n", mod);
	head = anthill->head_ways;
	int count = 0;
	int first_ant_pr = 0;
	int num_fr = 1;
	int num_cur = 1;
	int size_way_pr = 0;
	
	while (count != anthill->num_ants)
	{printf("1\n\n");
		head->size_ant = mod ? diff + 1 - head->size_way : diff - head->size_way;
		count =  head->size_ant + count;
		mod = mod ? mod - 1 : mod;
		//printf("head->first = %d\n", head->first_ant);
		if (head->first_ant == 1)
			head->first_ant = head->first_ant;
		else
			head->first_ant = (head->size_way - size_way_pr) * (num_cur - num_fr) + first_ant_pr + 1;
		//printf("head->first = %d\n", head->first_ant);
		first_ant_pr = head->first_ant;
		num_cur++;
		size_way_pr = head->size_way;
		printf("first_pr = %d\n", first_ant_pr);
		printf("num_pr = %d\n", num_fr);
		printf("num_cur = %d\n\n", num_cur);
		head = head->next;
	}

	h = anthill->head_ways;
	while (h)
	{
	printf ("\nh->size_ant = %d\n", h->size_ant);
	printf("h->size_way = %d\n", h->size_way);
	printf("h->first_ant = %d\n\n", h->first_ant);
	printf("anthill->max_path_len = %d\n", anthill->max_path_len);
	h = h->next;
	}
/*	if(anthill->head_ways->next == NULL)
	{
		while (anthill->head_ways->size_way)

	}*/
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
	set_ants_to_ways(anthill);
}