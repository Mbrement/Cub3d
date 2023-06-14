/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:11:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/14 15:33:39 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include "math.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"

# define WIN_W 1500
# define WIN_H 750

typedef struct s_map
{
	int	north;
	int	west;
	int	east;
	int	south;
	int	celing[3];
	int	floor[3];
}		t_map;

int		main(int argc, char **argv, char **envp);

//////PARSING//////
void	check_file(char *map);

//////EXEC//////

//////TOOLS//////

///TMP A DELETE///
char	*get_next_line(int fd);

#endif