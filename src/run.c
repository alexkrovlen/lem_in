# include "lem_in.h"

static int find_num_ant(t_anthill *anthill, t_way *head)
{
	int num_ant;
	int num_way;
	t_way *h;
	int *str;
	int i;

	i = 0;
	h = head;
	str = (int *)ft_memalloc(sizeof(int) * (anthill->num_of_ways - 1));
	while (h->next)
	{
		str[i] = h->next->first_ant;
		i++;
		h = h->next;
	}
	str[i] = '\0';
	i = 0;
	num_ant = head->first_ant;
	num_way = 1;
	h = anthill->head_ways;
	//printf("head->first_ant = %d\n", head->first_ant);
	while (head->first_ant != h->first_ant)
	{
		num_way++;
		h = h->next;
	}
	//printf ("num way = %d\n", num_way);
	while (head->struct_ant->next)
		head->struct_ant = head->struct_ant->next;
	//printf ("head->struct_ant-.num_ant = %d\n", head->struct_ant->num_ant);
	if (head->struct_ant->num_ant + num_way >= str[i])
	{
		while (head->struct_ant->num_ant + num_way >= str[i] && str[i] != '\0')
		{
			num_way++;
			i++;
		}
	}
	//printf ("num way = %d\n", num_way);
	//printf("head->struct_ant->num_ant = %d\n\n", head->struct_ant->num_ant);
	num_ant = head->struct_ant->num_ant + num_way;
	if (num_ant > anthill->num_ants)
		return (-1);
	return (num_ant);
	// проверить как будет работать на 3 и более путях
	// когда переходит на 3 путь на 1ом пути цифры должны тоже прибавляться больше,
	// то есть сравнивать нужно со всеми возможными некстами
	// ка вариает таое
	/*
	while (head->struct_ant->num_ant + num_way >= head->(от конца)->first_ant)
		while (head->struct_ant->num_ant + num_way >= head->(от конца) - 1->first_ant)
			...
				while (head->struct_ant->num_ant + num_way >= head->next->first_ant)
	*/
}

static t_ant	*new_ant(t_anthill *anthill, t_way *head)
{
	t_ant *list;

	if (!(list = (t_ant *)ft_memalloc(sizeof(t_ant))))
		return (NULL);
	list->num_ant = find_num_ant(anthill, head);
	list->next = NULL;
	return (list);
}

static t_ant *init_struct_ant(t_way *head, int num_ants)
{
	t_ant *struct_ant;

	struct_ant = (t_ant *)ft_memalloc(sizeof(t_ant));
	if (head->first_ant > num_ants)
		struct_ant->num_ant = 0;
	else
		struct_ant->num_ant = head->first_ant;
	struct_ant->next = NULL;
	return (struct_ant);
}

static void free_last_list(t_ant *ant)
{
	t_ant *list;

	list = ant;
	while (ant->next->next)
	{
		ant = ant->next;
	}
	free(ant->next);
	ant->next = NULL;
	ant = list;
}

static void size_ant(t_way *head)
{
	t_way *way;
	t_ant *ant;
	int count;

	way = head;
	//printf("way->struct_ant->num_ant = %d\n", way->struct_ant->num_ant);
	while (head)
	{
		count = 0;
		ant = head->struct_ant;
		while (ant && ant->num_ant > 0)
		{
			ant = ant->next;
			count++;
		}
		head->size_ant = count;
		head = head->next;
	}
	head = way;
	//printf("way = %d\n", head->first_ant);
}

void run_ants(t_anthill *anthill)
{
	int **res;
	int i;
	int j;
	int max_len;
	t_way *head;

	res = (int **)ft_memalloc(sizeof(int *) * anthill->num_ants);
	i = 0;
	j = 0;
	head = anthill->head_ways;
	while(head->next)
		head = head->next;
	max_len = head->size_way;
	//printf("max_len = %d\n", max_len);
	while (i < anthill->num_ants)
	{
		j = 0;
		res[i] = (int *)ft_memalloc(sizeof(int) * (anthill->num_ants * max_len));
		while (j < anthill->num_ants *max_len)
			res[i][j++] = -1;
		i++;
	}
	
	//print_way( res, anthill, max_len);
	i = 0;
	int count;
	int w;
	head = anthill->head_ways;
	while (head)
	{
		head->struct_ant = init_struct_ant(head, anthill->num_ants);
		head = head->next;
	}
	head = anthill->head_ways;
	int ttt = 1;
	t_ant *tmp;
	while (head)
	{
		ttt = 1;
		tmp = head->struct_ant;
		//printf("head->size_ant = %d\n", head->size_ant);
		while (ttt < head->size_ant)
		{//printf ("t = %d\n", ttt);
			head->struct_ant->next = new_ant(anthill, head);
			//printf("head->struct_ant->next  = %d\n", head->struct_ant->next->num_ant);
			if (head->struct_ant->next->num_ant == -1)
			{
				free_last_list(head->struct_ant);
				break ;
			}
			head->struct_ant = head->struct_ant->next;
			ttt++;
		}
		head->struct_ant = tmp;
		head = head->next;
	}
	head = anthill->head_ways;
	// t_way *h;
	// h = anthill->head_ways;
	// printf("START\n\n");
	// printf("num ants = %d\n", anthill->num_ants);
	// while (h)
	// {printf("size ant = %d\n", h->size_ant);
	// printf("size way = %d\n", h->size_way);
	// 	while (h->struct_ant)
	// 	{
	// 		printf("num_ant = %d  ", h->struct_ant->num_ant);
	// 		h->struct_ant = h->struct_ant->next;
	// 	}
	// 	printf("\n");
	// 	h = h->next;
	// }
//printf("STOP\n\n");
	//printf("STOP\n\n");
	// изменить запись
	//идти сначала пока есть head
	// смотреть какой муравей
	// искать этот номер - 1 в таблице res[i] и писать туда строку   mlmok
//printf("fffff =%d\n", head->struct_ant->num_ant);
	//printf("head->struct_ant->num_ant =%d\n", head->struct_ant->num_ant);
	size_ant(head);
	//printf("head->struct_ant->num_ant =%d\n\n", head->struct_ant->num_ant);
	// printf("head->size_ant = %d\n", head->size_ant);
	// printf("head->size_way = %d\n", head->size_way);
	// printf("STOP\n\n");

	//printf("head-> =%d\n", head->first_ant);
	while (head && head->size_ant > 0)
	{
		// printf("head->size_ant = %d\n", head->size_ant);
		// printf("head->size_way = %d\n", head->size_way);
		
		while (head->struct_ant)
		{
			//printf("head->struct_ant->num_ant = %d\n", head->struct_ant->num_ant);
			i = 0;
			w = 0;
			count = 0;
			j = 0;
			while (head->struct_ant->num_ant - 1 != i)
				i++;
			while (j < head->zero + head->size_way)
			{// printf("j = %d\n", j);
			// printf ("head->zero = %d\n", head->zero);
			// printf("head->size_way = %d\n", head->size_way);
				while (count++ < head->zero)
					j++;
				res[i][j] = head->way[w];
				w++;
				j++;
			}
			head->zero++;
			head->struct_ant = head->struct_ant->next;
		}
		//printf("!\n");
		head = head->next;
	}
	/*while (i < anthill->num_ants)
	{
		j = 0;
		count = 0;
		w = 0;
		while (j < head->zero + head->size_way)
		{
			while (count++ < head->zero)
				j++;
			res[i][j] = head->way[w];
			w++;
			j++;
		}
		head->zero++;
		i++;
	}*/
	//print_way( res, anthill, max_len);
	print_ants(res, anthill, max_len);
}

void 				print_way(int **res, t_anthill *anthill, int max_len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_printf("_________________________________________\n");
	while (i < anthill->num_ants)
	{
		j= 0;
		ft_printf ("%d | ", i);
		while (j < anthill->num_ants * max_len)
		{
			ft_printf("%d  ", res[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
