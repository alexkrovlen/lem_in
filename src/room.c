# include "lem_in.h"

void	room_add(t_anthill *anthill, t_room *room)
{
	if (room == NULL)
		return ;
	if (anthill->room_list == NULL)
	{
		anthill->room_list = room;
	}
	else
	{
		room->next = anthill->room_list;
		anthill->room_list = room;
	}
}

t_room	*room_new(char *name, int x, int y, int status)
{
	t_room	*room;

	if (!(room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(name);
	room->coord_x = x;
	room->coord_y = y;
	room->status = status;
	room->next = NULL;
	return (room);
}