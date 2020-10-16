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

t_room	*detect_room(t_anthill *anthill, char *line)
{
	t_room *room;
	

	return (room);
}

int	is_room(char *str)
{

}

static void	check_rooms(t_anthill *anthill)
{
	char	*line;
	t_room	*room;

	while (get_next_line(0, &line) > 0)
	{
		if(is_hash != 0)
		{
			map_add(&(anthill->map), ft_strdup(line));
			free(line);
		}
		else if (is_room(line))
		{
			room = detect_room(anthill, line)
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