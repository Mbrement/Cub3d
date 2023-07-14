/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:21:20 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/14 08:30:57 by mbrement         ###   ########lyon.fr   */
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
	float x;
	float y;
	// float W;
	// float H;

	// W = (float) *mlx.wall.east_height * 8;
	// H = (float) *mlx.wall.east_lenth * 8;
	y = 0;

	if (player.look < 90)
		{
			while (y++ < player.pos_y)
			{	x = 0;
				while (x++ < player.pos_x)
				{
					mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, x , player.pos_y, rgb);
					if ((int)1/(x / player.pos_x) == (int)1/(y / player.pos_y))
					{
						mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, x , y, rgb);
						mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, x - 1/(x / player.pos_x) , y - 1/(y / player.pos_y), rgb);
					}
				}
			}
		}
	else if (player.look < 180)
		{
			while (y++ < player.pos_y)
				mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, player.pos_x , y, rgb);
		}
	else if (player.look < 270)
		{
			while (x++ < player.pos_x)
				mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, x + player.pos_x  , player.pos_y, rgb);
		}
	else if (player.look <= 360)
		{
			while (y++ < player.pos_y)
				mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, player.pos_x , y + player.pos_y, rgb);
		}
}
