/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/13 16:53:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_wall	put_img_in_wall(t_map map, t_mlx mlx);

void	ft_mlx(t_map map)
{
	t_mlx	mlx;

	(void)map;
	mlx.mlx_init_ptr = mlx_init();
	if (!mlx.mlx_init_ptr)
	{
		printf("Mlx couldn't init\n");
		exit(1);
	}
	mlx.wall = put_img_in_wall(map, mlx);
	mlx.mlx_win_ptr = mlx_new_window(mlx.mlx_init_ptr, *mlx.wall.east_height * 2, *mlx.wall.east_height * 2, "cub3d");
	if (!mlx.mlx_win_ptr)
	{
		printf("Mlx create the window\n");
		exit(1);
	}
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.north, *mlx.wall.north_height, *mlx.wall.north_height); 
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.south, *mlx.wall.south_height, *mlx.wall.south_height);
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.east, *mlx.wall.east_height, *mlx.wall.east_height);
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.west, *mlx.wall.west_height, *mlx.wall.west_height);
	sleep(2);
	mlx_destroy_image(mlx.mlx_init_ptr, mlx.wall.north);
	mlx_destroy_image(mlx.mlx_init_ptr, mlx.wall.east);
	mlx_destroy_image(mlx.mlx_init_ptr, mlx.wall.south);
	mlx_destroy_image(mlx.mlx_init_ptr, mlx.wall.west);
	mlx_destroy_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr);
	mlx_destroy_display(mlx.mlx_init_ptr);
}
t_wall	put_img_in_wall(t_map map, t_mlx mlx)
{
	t_wall wall;

	wall.north= malloc(sizeof(void *));
	wall.north_height = malloc(sizeof(int *));
	wall.north_lenth = malloc(sizeof (int *));
	wall.south= malloc(sizeof(void *));
	wall.south_height = malloc(sizeof (int *));
	wall.south_lenth = malloc(sizeof (int *));
	wall.east= malloc(sizeof(void *));
	wall.east_height = malloc(sizeof (int *));
	wall.east_lenth = malloc(sizeof (int *));
	wall.west= malloc(sizeof(void *));
	wall.west_height = malloc(sizeof(int *));
	wall.west_lenth = malloc(sizeof (int *));
	wall.north = mlx_xpm_file_to_image(mlx.mlx_init_ptr, map.north_file, wall.north_height, wall.north_lenth);
	wall.east = mlx_xpm_file_to_image(mlx.mlx_init_ptr, map.south_file, wall.south_height, wall.south_lenth);
	wall.west = mlx_xpm_file_to_image(mlx.mlx_init_ptr, map.east_file, wall.east_height, wall.east_lenth);
	wall.south = mlx_xpm_file_to_image(mlx.mlx_init_ptr, map.west_file, wall.west_height, wall.west_lenth);
	return(wall);
}