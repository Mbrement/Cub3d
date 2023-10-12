/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:11:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/12 16:34:03 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include "../lib/mlx/mlx_int.h"

# define WIN_W 3000
# define WIN_H 1500
# define FOV 80
# define SPEED 0.05

typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	size_t	pixel_to_mapx;
	size_t	pixel_to_mapy;
}				t_data;

typedef struct s_map
{
	int		north;
	int		west;
	int		east;
	int		south;
	int		north_found;
	int		west_found;
	int		east_found;
	int		south_found;
	int		celing_found;
	int		floor_found;
	char	*north_file;
	char	*west_file;
	char	*east_file;
	char	*south_file;
	int		celing[3];
	int		floor[3];
	int		celing_color;
	int		floor_color;
	int		error;
	char	**map;
	size_t	y_lenth;
	size_t	x_lenth;
}		t_map;

typedef struct s_t_wall_data
{
	char		*addr;
	int			*bits_py_px;
	int			*size_line;
	int			*endian;
}	t_wall_data;

typedef struct s_wall
{
	void		*north;
	t_wall_data	north_data;
	int			north_height;
	int			north_lenth;
	void		*east;
	t_wall_data	east_data;
	int			east_height;
	int			east_lenth;
	void		*west;
	t_wall_data	west_data;
	int			west_height;
	int			west_lenth;
	void		*south;
	t_wall_data	south_data;
	int			south_height;
	int			south_lenth;
}		t_wall;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	look;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		turn_left;
	int		turn_right;
	int		boost;
}	t_player;

typedef struct s_mlx
{
	void		*mlx_init_ptr;
	void		*mlx_win_ptr;
	void		*mlx_img_ptr;
	t_wall		*wall;	
	t_player	*player;
	t_data		*data;
	t_data		*org;
	t_map		*map;
}		t_mlx;

typedef struct s_ray
{
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	double		raydirx;
	double		raydiry;
	double		camerax;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		perpwalldist;
	int			lineheight;
	double		pos_x;
	double		pos_y;
}					t_ray;

//////PARSING//////
t_map	check_file(char *map, t_map true_map);
int		check_chr_map(char **maps);
int		check_walls(t_map *map);
int		locate_player_x(char **maps);
int		locate_player_y(char **maps);

//////EXEC//////

//////MLX//////
void	ft_mlx(t_map *map, t_mlx *mlx);
int		key_pressed(int key, t_mlx *mlx);
int		key_released(int key, t_mlx *mlx);
int		ft_move(t_mlx *mlx);
int		handle_mouse(int x, int y, t_mlx *mlx);
void	put_player(t_mlx mlx, t_player player, int color);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color);
void	map_img(t_mlx *mlx, t_map map);
void	ft_ray(t_mlx *mlx);
int		refresh_img(t_mlx *mlx);
void	ft_draw_vertical_north(t_mlx *mlx, int screen_x, int *drawn, int x);
void	ft_draw_vertical_south(t_mlx *mlx, int screen_x, int *drawn, int x);
void	ft_draw_vertical_west(t_mlx *mlx, int screen_x, int *drawn, int x);
void	ft_draw_vertical_east(t_mlx *mlx, int screen_x, int *drawn, int x);
t_wall	*put_img_in_wall(t_map map, t_mlx mlx);

//////MATH//////
void	bresenham_cub(t_mlx mlx, double dest_x, double dest_y, int color);
int		is_valid_move_y(t_mlx *mlx, double new_y);
int		is_valid_move_x(t_mlx *mlx, double new_x);
int		is_valid_move(t_mlx *mlx, double new_x, double new_y);
void	road_to_wall(t_mlx *mlx, int y, int x, double angle);

//////TOOLS//////
void	end_of_prog(t_map map, char *err_msg);
void	end_of_prog_mlx(t_mlx *mlx);
int		ft_exit(int i, t_mlx *mlx);
void	data_wall(t_wall *wall);
int		nbr_of_key(t_mlx *mlx);

///TMP A DELETE///
char	*get_next_line(int fd);

#endif