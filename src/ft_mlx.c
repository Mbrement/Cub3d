/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/10 10:06:00 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

void	ray(t_mlx mlx, t_player player, int rgb);
t_wall	*put_img_in_wall(t_map map, t_mlx mlx);
void	init_game(t_mlx *mlx, t_map map);

void	ft_mlx(t_map *map, t_mlx *mlx)
{
	if (!mlx)
		end_of_prog(*map);
	mlx->map = map;
	mlx->data = malloc(sizeof(t_data));
	if (!mlx->data)
		end_of_prog_mlx(mlx);
	mlx->mlx_init_ptr = mlx_init();
	if (!mlx->mlx_init_ptr)
	{
		printf("Error\nMlx couldn't init\n");
		end_of_prog_mlx(mlx);
	}
	mlx->wall = put_img_in_wall(*map, *mlx);
	mlx->mlx_win_ptr = mlx_new_window(mlx->mlx_init_ptr, WIN_W, WIN_H, "cub3d");
	if (!mlx->mlx_win_ptr)
	{
		printf("Error\nMlx couldn't create the window\n");
		end_of_prog_mlx(mlx);
	}
	init_game(mlx, *map);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	if (y > WIN_H || x > WIN_W || y < 0 || x < 0)
		return ;
	dst = mlx->data->addr + (y * mlx->data->line_length + x * 4);
	*(unsigned int *)dst = color;
}

void	player_get_look(t_mlx *mlx, t_map map)
{
	char	c;

	c = map.map[locate_player_y(map.map)][locate_player_x(map.map)];
	if (c == 'N')
		mlx->player->look = 270;
	else if (c == 'E')
		mlx->player->look = 0;
	else if (c == 'S')
		mlx->player->look = 90;
	else if (c == 'W')
		mlx->player->look = 180;
}

void	init_game(t_mlx *mlx, t_map map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	mlx->player = player;
	player_get_look(mlx, map);
	mlx->map->x_lenth = 0;
	while (map.map[++mlx->map->x_lenth])
		;
	mlx->map->y_lenth = ft_strlen(map.map[1]) - 1;
	player->pos_x = locate_player_x(map.map) + 0.5;
	player->pos_y = locate_player_y(map.map) + 0.5;
	mlx_hook(mlx->mlx_win_ptr, 17, 1L << 1, ft_exit, NULL);
	mlx_do_key_autorepeatoff(mlx->mlx_init_ptr);
	mlx_hook(mlx->mlx_win_ptr, 2, 1L << 0, key_pressed, mlx);
	mlx_hook(mlx->mlx_win_ptr, 3, 1L << 1, key_released, mlx);
	mlx_mouse_move(mlx->mlx_init_ptr, mlx->mlx_win_ptr, WIN_W / 2, WIN_H / 2);
	mlx_mouse_hide(mlx->mlx_init_ptr, mlx->mlx_win_ptr);
	mlx_hook(mlx->mlx_win_ptr, MotionNotify,
		PointerMotionMask, &handle_mouse, mlx);
	mlx_loop_hook(mlx->mlx_init_ptr, refresh_img, mlx);
	mlx_loop(mlx->mlx_init_ptr);
}

t_wall	*put_img_in_wall(t_map map, t_mlx mlx)
{
	t_wall	*wall;

	wall = malloc(sizeof (t_wall));
	if (!wall)
		end_of_prog_mlx(&mlx);
	wall->north = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.north_file, &wall->north_height, &wall->north_lenth);
	wall->east = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.east_file, &wall->east_height, &wall->east_lenth);
	wall->west = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.west_file, &wall->west_height, &wall->west_lenth);
	wall->south = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.south_file, &wall->south_height, &wall->south_lenth);
	data_wall(wall);
	return (wall);
}
