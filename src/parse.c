# include "lem_in.h"

static int	count_of_ants(void)
{
	char	*line;

	while(get_next_line(0, &line) > 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			free(line);
			continue ;
		}
		else if (ft_strchr(line, ' ') != NULL || (ft_atoi(line)) <= 0)
		{
			free(line);
			exit_error();
		}
		else
			return (ft_atoi(line));
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
	room_add(anthill, room_new(array[0], ft_atoi(array[1]), ft_atoi(array[2]), *status));
	if (*status == 1)
		anthill->start = anthill->num_of_rooms;
	if (*status == 2)
		anthill->end = anthill->num_of_rooms;
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
	{printf("!\n");
		ft_free_split(array, 3);
		exit_error ();
	}
	ft_free_split(array, 3);
	return (1);
}

static void	check_rooms(t_anthill *anthill)
{
	char	*line;
	int		status;

	status = 0;
	while (get_next_line(0, &line) > 0)
	{
		printf("line = %s\n", line);
		if(is_hash(line) != 0)
		{
			status = is_hash(line);printf("status = %d\n", status);
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else if (is_room(line))
		{
			detect_room(anthill, line, &status);
		}
	}
}

void		parse(t_anthill *anthill)
{
	anthill->num_ants = count_of_ants();
	printf("ants = %d\n", anthill->num_ants);
	check_rooms(anthill);
	printf("ok\n");
}
