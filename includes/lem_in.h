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

typedef struct		s_queue
{
	int				num;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_anthill
{
	int				num_of_rooms;
	t_room			*room_list;
	t_ways			*head_ways;
	int				**table_links; // можно попробовать сделать структуру соседей чтоб потом удалять
	char			**table_name;
	int				start;
	int				end;
	t_map			*map;
	int				num_ants;
	int				*used;
	int				*parent;
	int				*path_len;
	int				max_path_len;
	int				num_of_paths;
}					t_anthill;

# define START 1
# define END 2
# define COMMENT 3

void				parse(t_anthill *anthill);
t_anthill			*init_anthill(void);
void				map_add(t_map **head, char *str);
void				exit_error(void);
void  				ft_free_split(char **str, int j);
void				room_add(t_anthill *anthill, t_room *room);
t_room				*room_new(char *name, int x, int y, int status);
int					ft_atoi_new(char *str);
void				detect_room(t_anthill *anthill, char *line, int *status);
int					is_room(char *str);
int					is_hash(char *str);
int					is_links(char *str);
void 				print_table(t_anthill *anthill);
void 				print_map(t_anthill *anthill);
void				this_is_match(t_anthill *anthill);
void				algo(t_anthill *anthill);
void				algo_bfs(t_anthill *anthill);
t_queue				*push_queue(t_queue *queue, int n);
t_queue				*pop_queue(t_queue *q);
int					empty_queue(t_queue *q);
#endif