/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:13:57 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/20 23:19:13 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* header*/
# include "get_next_line.h"
# include "ft_printf.h"

/* mlx library */
# include <mlx.h>

/* library */
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

/* define */
# define IMG_SIZE	32
# define MAX_MAP	100

# define EMPTY	'0'
# define WALL	'1'
# define GOAL	'E'
# define COLLECTS	'C'
# define PASSED	'3'

# define XPM_EMPTY		"textures/empty.xpm"
# define XPM_WALL		"textures/wall.xpm"
# define XPM_COLLECT	"textures/collects.xpm"
# define XPM_EXIT		"textures/exit.xpm"
# define XPM_PLAYER		"textures/souzou_got_01.xpm"

/* struct */
typedef struct pos
{
	int	i;
	int	j;
}				t_pos;

typedef struct s_img
{
	void	*em_img;
	void	*wall_img;
	void	*col_img;
	void	*exit_img;
	void	*p_img;
}				t_img;

typedef struct s_dat
{
	void		*mlx;
	void		*win;
	t_img		*img;
	int			count;
	int			coll_con;
	int			y_column;
	int			x_row;
	void		*p[MAX_MAP][MAX_MAP];
	char		**map;
	t_pos		player;
	t_pos		exit;
}				t_data;

typedef struct queue
{
	int		tail;
	int		head;
	t_pos	*wait_que;
	int		max_size;
}			t_queue;

/* init struct */
void	init_img(t_img *img);
void	init_data(t_data *data, t_img *img);
void	fill_data(t_data *data, t_img *img, char *filename);

/* fill img */
void	*read_img(t_data *data, void *mlx, char *filename);
void	fill_img(t_data *data, t_img *img);

/* fill map */
void	fill_map(t_data *data, char *filename);
void	read_map_line(t_data *data, char **map, int fd);
bool	validate_extension(char *filename);
bool	validate_mapsize(t_data *data, char *line, int i, int j);
void	exit_during_read(t_data *data, char *line, char *msg, int j);
int		set_map_elements(t_data *data, char *line, int i, int j);

/* validate_map */
bool	is_surrounded_walls(t_data *data, t_img *img, int width, int height);
void	validate_map_format(t_data *data, int width, int height);
void	validate_number_elements(t_data *data, int width, int height);
bool	are_dup_p_e(t_data *data, t_img *img, int width, int height);

/* bsf cheack */
bool	can_goal(t_data *data, char **bfs, int x, int y);
bool	bfs_search(t_data *data, t_queue *que, char **map);
void	enqueue_next_pos(t_data *data, t_queue *que, t_pos *cur);
bool	did_search(char **map, t_pos *cur, int *collect, bool *goal);
bool	is_passable(t_data *data, char **map, int x_i, int y_j);
void	init_queue(t_data *data, t_queue *que, int width, int height);
void	enqueue(t_queue *que, int i, int j);
t_pos	*dequeue(t_queue *que);
void	free_queue(t_queue *que);

/* window */
void	disply_img(t_data *data, void *p_img[MAX_MAP][MAX_MAP]);
int		window_close(t_data *data);

/* event */
int		key_push(int keycode, t_data *data);
void	move_player_y(t_data *data, int x, int y, int m);
void	move_player_x(t_data *data, int x, int y, int m);
bool	can_move(t_data *data, t_img *img, void *p_next);

/* frees */
void	free_data(t_data *data);
void	free_map(t_data *data, int rows);
void	free_img(t_data *data, t_img *img);

/* utils */
int		exit_ft_printf(char *msg, t_data *data);
int		exit_perror(char *msg, t_data *data);
#endif
