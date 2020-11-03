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
	if (!anthill->used[anthill->end] /*|| anthill->max_path_len - anthill->path_len[anthill->end] < 2*/)
		return (0);
	all_ways(anthill);
	return (1);
}

static t_anthill		*delete_rooms(t_anthill *anthill)
{
	int			i;
	int			j;

	i = anthill->parent[anthill->end];
	j = anthill->end;
	while (anthill->used[anthill->start] != 0)
	{
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
	i = 0;
	while (i < anthill->num_of_rooms)
	{
		if (anthill->used[i] == 1)
			anthill->used[i] = 0;
		i++;
	}
	return (anthill);
}

static void set_ants_to_ways(t_anthill *anthill)
{
	t_way *head;
	int size_way;
	int diff;
	int mod;

	size_way = 0;
	head = anthill->head_ways;
	if (head == NULL)
		exit_error ();
	while (head)
	{
		size_way = size_way + head->size_way;
		head = head->next;
	}
	//anthill->max_path_len = size_way + anthill->num_ants;
	//diff = anthill->max_path_len / anthill->num_of_ways;
	mod = anthill->max_path_len % anthill->num_of_ways;
	head = anthill->head_ways;
	int first_ant_pr = 0;
	int num_fr = 1;
	int num_cur = 1;
	int size_way_pr = 0;

	int i;
	i = 0;
	t_way *h;
	h = anthill->head_ways;
	while (h->next)
	{
		//printf("h->size_way = %d\n", h->size_way);
		h = h->next;
	}
	int max_way_len;
	max_way_len = h->size_way;
//	printf("max_way_len = %d\n\n", max_way_len);
	diff = (size_way + anthill->num_ants) / anthill->num_of_ways;
//	printf("diff = %d\n", diff);
	while (head)
	{
		if (diff - head->size_way > 0)
			head->size_ant = diff - head->size_way;
		else
			head->size_ant = 0;
		// if (i < anthill->num_ants)
		// {
		// 	printf("head->size_way = %d\n", head->size_way);
		// 	printf("max_way_len = %d\n", max_way_len);
		// 	printf("anthill->num_ants = %d\n", anthill->num_ants);
		// 	printf("i = %d\n\n", i);
		// 	if (max_way_len - head->size_way + i < anthill->num_ants)
		// 	{
		// 		i = max_way_len - head->size_way + i;
		// 		head->size_ant = max_way_len - head->size_way;
		// 	}
		// 	else
		// 	{
		// 		head->size_ant = anthill->num_ants - i;
		// 		i = anthill->num_ants;
		// 	}
		//	}
		if (head->first_ant == 1)
			head->first_ant = head->first_ant;
		else
			head->first_ant = (head->size_way - size_way_pr) * (num_cur - num_fr) + first_ant_pr + 1;
		first_ant_pr = head->first_ant;
		num_cur++;
		size_way_pr = head->size_way;
		head = head->next;
	}
	// diff = (anthill->num_ants - i) / anthill->num_of_ways;
	// mod = (anthill->num_ants - i) % anthill->num_of_ways;
	// head = anthill->head_ways;
	// printf("head->size_ants = %d\n", head->size_ant);
	// printf("head->size_ants = %d\n", head->next->size_ant);
	// printf("head->size_ants = %d\n", head->next->next->size_ant);
	// printf("head->size_ants = %d\n", head->next->next->next->size_ant);
	// printf("head->size_ants = %d\n", head->next->next->next->next->size_ant);
	// if (diff == 0 && mod == 0)
	// 	return ;
	// while (head)
	// {
	// 	head->size_ant = mod ? (diff + 1 + head->size_ant) : (diff + head->size_ant);
	// 	mod = mod ? mod - 1 : mod;
	// 	head = head->next;
			
	// }
	//printf("head->size_ants = %d\n", head->size_ant);
}

static void check_first_and_size(t_anthill *anthill)
{
	t_way *head;

	head = anthill->head_ways;
	while (head)
	{
		if (head->size_ant == 0)
			head->first_ant = 0;
		head = head->next;
	}
}

void 	algo(t_anthill *anthill)
{
	int flag;

	
	flag = start_end_neighbor(anthill);
	if ( flag == 1 && start_have_one_link(anthill))
		this_is_match(anthill);
	
	init_for_alg(anthill);
	bzero_for_alg(anthill);
	anthill->num_of_ways = 0;
	if (flag == 1)
	{
		anthill->parent[anthill->end] = anthill->start;
		anthill->path_len[anthill->end] = 1;
		all_ways(anthill);
		anthill->table_links[anthill->end][anthill->start] = 0;
		anthill->table_links[anthill->start][anthill->end] = 0;
		anthill->path_len[anthill->end] = -1;
		anthill->parent[anthill->end] = -1;
	}
	while (find_way(anthill))
	{
		anthill = delete_rooms(anthill);
		//bzero_for_alg(anthill);
	}
	set_ants_to_ways(anthill);
	check_first_and_size(anthill);
}