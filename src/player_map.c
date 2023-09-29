/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:21:20 by mbrement          #+#    #+#             */
/*   Updated: 2023/09/29 14:31:52 by ngennaro         ###   ########.fr       */
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
	float	x_angle;
	float	y_angle;
	float	x_angle_tmp;
	float	y_angle_tmp;
	float	cor;
	float	radiant;
	int i;
	// float	tmp_cos;
	// float	tmp_sin;

	(void)player;
	i = 0;
	cor = (int)((FOV * -1) / 2);
	radiant = (M_PI / 180);
	while (cor < (int)(FOV / 2))
	{
		x_angle = mlx.player->pos_x;
		y_angle = mlx.player->pos_y;
		// tmp_cos = cosf((mlx.player->look + cor) * radiant) * mlx.org->pixel_to_mapx;
		// tmp_sin = sinf((mlx.player->look + cor) * radiant) * mlx.org->pixel_to_mapy;
		
		while (1)
		{
			x_angle_tmp = sinf(((mlx.player->look + cor) * radiant)) * mlx.org->pixel_to_mapx + x_angle;
			y_angle_tmp = cosf(((mlx.player->look + cor) * radiant)) * mlx.org->pixel_to_mapy + y_angle;
			if (!is_valid_move(&mlx, y_angle_tmp, x_angle_tmp))
			{
				// x_angle = x_angle_tmp;
				// y_angle = y_angle_tmp;
				while (is_valid_move(&mlx, y_angle, x_angle))
				{
					x_angle += sin(mlx.player->look * (M_PI / 180));
					y_angle += cos(mlx.player->look * (M_PI / 180));
				}
				break;
			}
			x_angle = x_angle_tmp;
			y_angle = y_angle_tmp;
		}
		// my_mlx_pixel_put(&mlx, x_angle, y_angle, rgb);
		// printf("%f\n",y_angle);
		bresenham_cub(mlx, x_angle, y_angle, rgb);
		cor += ((float)FOV / WIN_W);
		i++;
	}
	// road_to_wall(&mlx, y_angle, x_angle, cor);
}
	