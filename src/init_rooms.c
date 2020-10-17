# include "lem_in.h"

t_anthill		*init_anthill(void)
{
	t_anthill *anthill;

	if (!(anthill = (t_anthill *)ft_memalloc(sizeof(t_anthill))))
		return (NULL);
	anthill->num_of_rooms = 0;
	anthill->start = -1;
	anthill->end = -1;
	anthill->room_list = NULL;
	//anthill->table_name = NULL;
	//anthill->table_paths = NULL;
	anthill->head_ways = NULL;
	anthill->map = NULL;
	anthill->num_ants = 0;
	return (anthill);
}