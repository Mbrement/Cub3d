/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:04:32 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/19 11:30:47 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_hook(int key, t_mlx *mlx)
{
	if (key == 65307)
		exit(0);
	else if (key == 65364)
	{
		printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->pos_y += (float)mlx->org->pixel_to_mapy / 10;
	}
	else if (key == 115)
	{
		//W key;
		mlx->player->pos_y += ((float)mlx->org->pixel_to_mapy / 10) * (int)(mlx->player->look);
		mlx->player->pos_x += ((float)mlx->org->pixel_to_mapx / 10) * ((mlx->player->look))
	} 
	else if (key == 119 || key == 65362)
	{
		printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->pos_y -= (float)mlx->org->pixel_to_mapy / 10;
	}
	else if (key == 97 || key == 65361)
	{
		printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->pos_x -= (float)mlx->org->pixel_to_mapx / 10;
	}
	else if (key == 100 || key == 65363)
	{
		printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->pos_x += (float)mlx->org->pixel_to_mapx / 10;
	}
	else if (key == 113)
	{
		printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->look -= 5;
	}
	else if (key == 101)
	{
		printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->look += 5;
	}
	while (mlx->player->look < 0)
		mlx->player->look += 360;
	while (mlx->player->look >= 360)
		mlx->player->look -= 360;
	return (0);
}


// left_arrow  65363
// right_arrow 65361
// up_arrow 65362
// down_arrow 65364
// W 119
// A 97
// S 115
// D 100
// escape 65307
// Q  113
// E 101