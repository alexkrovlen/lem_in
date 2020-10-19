# include "lem_in.h"

static int	count_of_ants(t_anthill *anthill)
{
	char	*line;

	while(get_next_line(0, &line) > 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
			continue ;
		}
		else if (ft_strchr(line, ' ') != NULL || (ft_atoi(line)) <= 0)
		{
			free(line);
			exit_error();
		}
		else
		{
			map_add(&(anthill->map), ft_strdup(line));
			return (ft_atoi(line));
		}
	}
	return (0);
}

int	is_hash(char *str)
{
	if (!ft_strcmp(str, "##start"))
		return (START);
	else if (!ft_strcmp(str, "##end"))
		return (END);
	else if (str[0] == '#' && str[1] != '#')
		return (COMMENT);
	else
		return(0);	
}

void	detect_room(t_anthill *anthill, char *line, int *status)
{
	char	**array;
	
	array = ft_strsplit(line, ' ');
	if (*status == 3)
		*status = 0;
	//printf("status = %d\n", *status);
	//printf ("start = %d\nend = %d\n", anthill->start, anthill->end);
	room_add(anthill, room_new(array[0], ft_atoi(array[1]), ft_atoi(array[2]), *status));
	if (*status == 1 && anthill->start == -1)
		anthill->start = anthill->num_of_rooms;
	else if (*status == 2 && anthill->end == -1)
		anthill->end = anthill->num_of_rooms;
	/*else
	{
		//free anthill ...
		printf("?\n");
		exit_error ();
	}*/
	*status = 0;
	anthill->num_of_rooms++;
	ft_free_split(array, 3);
	return ;
}

int	is_room(char *str)
{
	char	**array;

	if (ft_word_count(str, ' ') != 3)
		return (0);
	array = ft_strsplit(str, ' ');
	if (array[0][0] == 'L' || ft_isdigit(ft_atoi_new(array[1])) == 0 || ft_isdigit(ft_atoi_new(array[2])) == 0)
	{
		//printf("!\n");
		ft_free_split(array, 3);
		exit_error ();
	}
	ft_free_split(array, 3);
	return (1);
}

int		is_links(char *str)
{
	if (ft_strchr(str, '-') == NULL)
		return (0);
	return (1);
}

int 	create_table_links(t_anthill *anthill)
{
	int count;
	t_room *room;
	int i;

	count = 0;
	room = anthill->room_list;
	if (!(anthill->table_links = (int **)ft_memalloc(sizeof(int *) * anthill->num_of_rooms)))
		return (1);
	if (!(anthill->table_name = (char **)ft_memalloc(sizeof(char *) * anthill->num_of_rooms)))
		return (1);
	while (count < anthill->num_of_rooms)
	{
		i = 0;
		if (!(anthill->table_links[count] = (int *)ft_memalloc(sizeof(int) * anthill->num_of_rooms)))
			return (1);
		else
		{
			while (i < anthill->num_of_rooms)
			{
				anthill->table_links[count][i] = 0;
				i++;
			}
		}
		anthill->table_name[count] = ft_strdup(room->name);
		room = room->next;
		count++;
	}
	anthill->start = anthill->num_of_rooms - anthill->start -1;
	anthill->end = anthill->num_of_rooms - anthill->end - 1;
	return (0);
}

void	links_add(t_anthill *anthill, char *line)
{
	char **str;
	int first;
	int second;
	int num;

	if (anthill->table_links == NULL && anthill->table_name == NULL)
	{
		if (create_table_links(anthill))
			exit_error (); //free all
	}
	str = ft_strsplit(line, '-');
	num = anthill->num_of_rooms - 1;
	while (num >= 0)
	{
		if (ft_strequ(anthill->table_name[num], str[0]))
			first = num;
		if (ft_strequ(anthill->table_name[num], str[1]))
			second = num;
		num--;
	}
	//printf ("first = %d\n second = %d\n", first, second);
	anthill->table_links[first][second] = 1;
	anthill->table_links[second][first] = 1;
}

static void	check_rooms(t_anthill *anthill)
{
	char	*line;
	int		status;

	status = 0;
	while (get_next_line(0, &line) > 0)
	{
		//printf("line = %s\n", line);
		if(is_hash(line) != 0)
		{
			status = is_hash(line);//printf("status = %d\n", status);
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else if (is_room(line))
		{//printf("!\n");
			detect_room(anthill, line, &status);
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else if (is_links(line) && anthill->start != -1 && anthill->end != -1)
		{
			links_add(anthill, line);
			//print_table(anthill);
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else
		{
			exit_error ();
			//free all
		}
		
	}
}

void		parse(t_anthill *anthill)
{
	anthill->num_ants = count_of_ants(anthill);
	//printf("ants = %d\n", anthill->num_ants);
	check_rooms(anthill);
	print_table(anthill);
	print_map(anthill);
	printf("start = %d\n", anthill->start);
	printf("end = %d\n", anthill->end);
	printf("ok\n");
}
