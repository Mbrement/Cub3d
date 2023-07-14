/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:27:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/14 11:21:49 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	bresenham_cub(t_mlx mlx, float dest_x, float dest_y, int color)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	float	rationel[3];

	(void)color;

	dy = dest_y - mlx.player->pos_y;
	dx = dest_x - mlx.player->pos_x;
	y = (int)mlx.player->pos_y;
	rationel[0] = 0.0;
	rationel[1] = (float)(dx / dy);
	rationel[2] = -1.0;
	x = (int)mlx.player->pos_x;
	while (x++ < (int)dest_x)
	{
		printf("ouet\n");
		mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, x, y, UINT32_MAX);
		// rationel[0] = rationel[0] + rationel[1];
		if (rationel[0] > 0.5)
		{
			y++;
			rationel[0] = rationel [0] - rationel[2];
		}
	}
		// rationel[0] = rationel[0] + rationel[1];
	while (x-- > (int)dest_x)
	{
		mlx_pixel_put(mlx.mlx_init_ptr, mlx.mlx_win_ptr, x, y, UINT32_MAX);
		if (rationel[0] > 0.5)
		{
			y++;
			rationel[0] = rationel [0] - rationel[2];
		}
	}
}

