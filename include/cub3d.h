/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:11:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/14 05:45:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "math.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include "../lib/mlx/mlx_int.h"

# define WIN_W 1500
# define WIN_H 750

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
	int		player_x;
	int		player_y;
}		t_map;

typedef struct s_wall
{
	void	*north;
	int		*north_height;
	int		*north_lenth;
	void	*east;
	int		*east_height;
	int		*east_lenth;
	void	*west;
	int		*west_height;
	int		*west_lenth;
	void	*south;
	int		*south_height;
	int		*south_lenth;
}		t_wall;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	look;
}	t_player;

typedef struct s_mlx
{
	void		*mlx_init_ptr;
	void		*mlx_win_ptr;
	t_wall		wall;	
	t_player	*player;
}		t_mlx;


int		main(int argc, char **argv, char **envp);

//////PARSING//////
t_map	check_file(char *map);
int		check_chr_map(char **maps);
int		check_walls(t_map map);
int		locate_player_x(char **maps);
int		locate_player_y(char **maps);

//////EXEC//////

//////MLX//////
void	ft_mlx(t_map map);
int		ft_hook(int key, t_player *player);
void	put_player(t_mlx mlx, t_player player, int color);

//////TOOLS//////
void	end_of_prog(t_map map);

///TMP A DELETE///
char	*get_next_line(int fd);

#endif