/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_in_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:00:10 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/12 18:36:54 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_wall	*put_img_in_wall(t_map map, t_mlx *mlx)
{
	t_wall	*wall;

	wall = malloc(sizeof (t_wall));
	if (!wall)
	{
		mlx->wall = wall;
		end_of_prog_mlx(mlx);
	}
	wall->north = mlx_xpm_file_to_image(mlx->mlx_init_ptr, \
		map.north_file, &wall->north_height, &wall->north_lenth);
	wall->east = mlx_xpm_file_to_image(mlx->mlx_init_ptr, \
		map.east_file, &wall->east_height, &wall->east_lenth);
	wall->west = mlx_xpm_file_to_image(mlx->mlx_init_ptr, \
		map.west_file, &wall->west_height, &wall->west_lenth);
	wall->south = mlx_xpm_file_to_image(mlx->mlx_init_ptr, \
		map.south_file, &wall->south_height, &wall->south_lenth);
	if (!wall->north || !wall->east || !wall->west || !wall->south)
	{
		mlx->wall = wall;
		mlx->player = NULL;
		end_of_prog_mlx(mlx);
	}
	data_wall(wall);
	return (wall);
}
