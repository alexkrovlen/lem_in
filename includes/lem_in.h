/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:50:34 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/05 20:26:58 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct		s_ant
{
	int				num_ant;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_way
{
	int				zero;
	t_ant			*struct_ant;
	int				first_ant;
	int				size_ant;
	int				size_way;
	int				*way;
	struct s_way	*next;
}					t_way;

typedef struct		s_queue
{
	int				num;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_anthill
{
	int				num_of_rooms;
	t_room			*room_list;
	t_way			*head_ways;
	int				**table_links;
	char			**table_name;
	int				start;
	int				end;
	t_map			*map;
	int				num_ants;
	int				*used;
	int				*parent;
	int				*path_len;
	int				max_path_len;
	int				num_of_ways;
}					t_anthill;

# define START 1
# define END 2
# define COMMENT 3
# define IGNOR 4

void				parse(t_anthill *anthill);
t_anthill			*init_anthill(void);
void				map_add(t_map **head, char *str);
void				exit_error(void);
void				ft_free_split(char **str, int j);
void				room_add(t_anthill *anthill, t_room *room);
t_room				*room_new(char *name, int x, int y, int status);
int					ft_atoi_new(char *str);
void				detect_room(t_anthill *anthill, char *line, int *status);
int					is_room(char *str);
int					is_hash(char *str, t_anthill *anthill);
int					is_links(char *str);
void				print_table(t_anthill *anthill);
void				print_map(t_anthill *anthill);
void				this_is_match(t_anthill *anthill);
void				algo(t_anthill *anthill);
void				algo_bfs(t_anthill *anthill);
t_queue				*push_queue(t_queue *queue, int n);
t_queue				*pop_queue(t_queue *q);
int					empty_queue(t_queue *q);
void				all_ways(t_anthill *anthill);
void				run_ants(t_anthill *anthill);
void				print_way(long long int **res, t_anthill *anthill, int max_len);
void				print_ants(long long int **res, t_anthill *anthill, int max_len);
void				free_error(t_anthill *anthill, char *line);
void				free_all(t_anthill *anthill);
void				free_res(long long int **res, int size);

#endif