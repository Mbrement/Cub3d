/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:21:20 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/17 16:41:59 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_player(t_mlx mlx, t_player player, int color)
{
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x, (int)player.pos_y + 1, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x, (int)player.pos_y, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x, (int)player.pos_y + 2, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x + 2, (int)player.pos_y + 1, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x + 2, (int)player.pos_y, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x + 2, (int)player.pos_y + 2, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x + 1, (int)player.pos_y + 1, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x + 1, (int)player.pos_y, color);
	mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, (int)player.pos_x + 1, (int)player.pos_y + 2, color);
}

void ray (t_mlx mlx, t_player player, int rgb)
{
	float 	x_angle;
	float	y_angle;
	float	cor;
	float	radiant;

	(void)player;
	cor = -30.0;
	radiant = M_PI / 180;
	while (cor ++ < 30)
	{
		x_angle = sinf((mlx.player->look + cor) * radiant) * 300 + mlx.player->pos_x;
		y_angle = cosf((mlx.player->look + cor) * radiant) * 300 + mlx.player->pos_y;
		bresenham_cub(mlx, x_angle, y_angle, rgb);
	}
}