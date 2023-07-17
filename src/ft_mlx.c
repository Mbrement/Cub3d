/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/17 16:41:47 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdint.h>

void	ray(t_mlx mlx, t_player player, int rgb);
t_wall	put_img_in_wall(t_map map, t_mlx mlx);
void	create_map(t_mlx mlx, t_map map);

void	ft_mlx(t_map map)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	(void)map;
	mlx->mlx_init_ptr = mlx_init();
	if (!mlx->mlx_init_ptr)
	{
		printf("Mlx couldn't init\n");
		exit(1);
	}
	mlx->wall = put_img_in_wall(map, *mlx);
	mlx->mlx_win_ptr = mlx_new_window(mlx->mlx_init_ptr, *mlx->wall.north_height * 8, *mlx->wall.north_height * 8, "cub3d");
	if (!mlx->mlx_win_ptr)
	{
		printf("Mlx create the window\n");
		exit(1);
	}
	create_map(*mlx, map);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.north);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.east);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.south);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.west);
	mlx_destroy_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr);
	mlx_destroy_display(mlx->mlx_init_ptr);
}

int	ft_dmg_control(int key, t_mlx *mlx)
{
	ray (*mlx, *mlx->player, 0);
	put_player(*mlx, *mlx->player, 0);
	ft_hook(key, mlx->player);
	put_player(*mlx, *mlx->player, UINT32_MAX);
	ray (*mlx, *mlx->player, UINT32_MAX);
	return (1);
}

//debug
int	ft_exit(int i)
{
	exit(i);
	return(0);
}
//endofdebug

void	create_map(t_mlx mlx, t_map map)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->pos_x = *mlx.wall.east_height * 4;
	player->pos_y = *mlx.wall.east_lenth * 4;
	player->look = 0;
	mlx.player = player;
	//debug
	(void)map;
	//endofdebug
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.north, 0, 0); 
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.south, 0, *mlx.wall.south_lenth * 7);
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.east, *mlx.wall.east_height * 7, 0);
	mlx_put_image_to_window(mlx.mlx_init_ptr, mlx.mlx_win_ptr, mlx.wall.west, *mlx.wall.west_height * 7, *mlx.wall.west_lenth * 7);
	put_player(mlx, *player, UINT32_MAX);
	mlx_hook(mlx.mlx_win_ptr, 17, 1L << 1, ft_exit, NULL);
	mlx_key_hook(mlx.mlx_win_ptr, ft_dmg_control, &mlx);
	mlx_loop(mlx.mlx_init_ptr);
}

t_wall	put_img_in_wall(t_map map, t_mlx mlx)
{
	t_wall	wall;

	wall.north = malloc(sizeof(void *));
	wall.north_height = malloc(sizeof(int *));
	wall.north_lenth = malloc(sizeof (int *));
	wall.south = malloc(sizeof(void *));
	wall.south_height = malloc(sizeof (int *));
	wall.south_lenth = malloc(sizeof (int *));
	wall.east = malloc(sizeof(void *));
	wall.east_height = malloc(sizeof (int *));
	wall.east_lenth = malloc(sizeof (int *));
	wall.west = malloc(sizeof(void *));
	wall.west_height = malloc(sizeof(int *));
	wall.west_lenth = malloc(sizeof (int *));
	wall.north = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.north_file, wall.north_height, wall.north_lenth);
	wall.east = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.south_file, wall.south_height, wall.south_lenth);
	wall.west = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.east_file, wall.east_height, wall.east_lenth);
	wall.south = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.west_file, wall.west_height, wall.west_lenth);
	return (wall);
}
