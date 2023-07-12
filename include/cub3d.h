/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:11:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/12 17:52:27 by mbrement         ###   ########lyon.fr   */
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
}		t_map;

int		main(int argc, char **argv, char **envp);

//////PARSING//////
t_map	check_file(char *map);

//////EXEC//////


//////MLX//////
void	ft_mlx(t_map map);

//////TOOLS//////
void	end_of_prog(t_map map);

///TMP A DELETE///
char	*get_next_line(int fd);

#endif