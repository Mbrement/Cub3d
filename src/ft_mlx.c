/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/12 19:10:31 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray(t_mlx mlx, t_player player, int rgb);
void	init_game(t_mlx *mlx, t_map map);

void	ft_mlx(t_map *map, t_mlx *mlx)
{
	if (!mlx)
		end_of_prog(*map, "Error\nMalloc error\n");
	mlx->map = map;
	mlx->data = malloc(sizeof(t_data));
	if (!mlx->data)
	{
		nfree((void **)&mlx);
		end_of_prog(*map, "Error\n");
	}
	mlx->mlx_init_ptr = mlx_init();
	if (!mlx->mlx_init_ptr)
	{
		nfree((void **)&mlx->data);
		nfree((void **)&mlx);
		end_of_prog(*map, "Error\nMLX couldn't initiate\n");
	}
	mlx->mlx_win_ptr = mlx_new_window(mlx->mlx_init_ptr, WIN_W, WIN_H, "cub3d");
	if (!mlx->mlx_win_ptr)
	{
		printf("Error\nMlx couldn't create the window\n");
		end_of_prog_mlx(mlx);
	}
	mlx->wall = put_img_in_wall(*map, mlx);
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

static void	ft_fill_player(t_player *player)
{
	player->boost = 0;
	player->move_down = 0;
	player->move_up = 0;
	player->move_right = 0;
	player->move_left = 0;
	player->turn_left = 0;
	player->turn_right = 0;
}

void	init_game(t_mlx *mlx, t_map map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	mlx->player = player;
	if (!player)
		end_of_prog_mlx(mlx);
	ft_fill_player(player);
	mlx->player->boost = 0;
	player_get_look(mlx, map);
	mlx->map->x_lenth = 0;
	while (map.map[++mlx->map->x_lenth])
		;
	mlx->map->y_lenth = ft_strlen(map.map[1]) - 1;
	player->pos_x = locate_player_x(map.map) + 0.5;
	player->pos_y = locate_player_y(map.map) + 0.5;
	mlx_hook(mlx->mlx_win_ptr, 17, 1L << 1, (void *)end_of_prog_mlx, mlx);
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

