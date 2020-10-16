#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct		s_map
{
	char			*str;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				status;
	struct s_room	*next;
}					t_room;

typedef struct		s_ways
{
	int				size_way;
	int				*way;
	int				size_ant;
	//t_ant			*ant_head;
	struct s_path	*next;
}					t_ways;


typedef struct		s_anthill
{
	int				num_of_rooms;
	t_room			*room_list;
	t_ways			*head_ways;
	//int			**table_paths;
	//char			**table_name;
	int				start;
	int				end;
	t_map			*map;
	int				num_ants;
}					t_anthill;

# define START 1
# define END 2
# define COMMENT 3

void				parse(t_anthill *anthill);
t_anthill			*init_anthill(void);
void				map_add(t_map **head, char *str);
void	exit_error(void);

#endif