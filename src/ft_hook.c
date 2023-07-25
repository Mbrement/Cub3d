/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:04:32 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/25 16:19:41 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_move_x(t_mlx *mlx, float new_x)
{
	int		x;
	int		y;
	char	c;

	x = (int)floor(new_x / mlx->org->pixel_to_mapx);
	y = (int)floor(mlx->player->pos_y / mlx->org->pixel_to_mapy) + 1;
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}

int	is_valid_move(t_mlx *mlx, float new_y, float new_x)
{
	int		x; 
	int		y;
	char	c;

	x = (int)floor(new_x / mlx->org->pixel_to_mapx);
	y = (int)floor(new_y / mlx->org->pixel_to_mapy) + 1;
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}

int	is_valid_move_y(t_mlx *mlx, float new_y)
{
	int		x; 
	int		y;
	char	c;

	x = (int)floor(mlx->player->pos_x / mlx->org->pixel_to_mapx);
	y = (int)floor(new_y / mlx->org->pixel_to_mapy) + 1;
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}

int	ft_hook(int key, t_mlx *mlx)
{
	float	new_x;
	float	new_y;

	new_x = mlx->player->pos_x;
	new_y = mlx->player->pos_y;
	if (key == 65307)
		exit(0);
	else if (key == 119 || key == 65362)
	{
		// printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		new_x += SPEED * sin(mlx->player->look * M_PI / 180);
		new_y += SPEED * cos(mlx->player->look * M_PI / 180);
	}
	else if (key == 115 || key == 65364)
	{
		// printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		new_x -= SPEED * sin(mlx->player->look * M_PI / 180);
		new_y -= SPEED * cos(mlx->player->look * M_PI / 180);
	}
	else if (key == 100 || key == 65361)
	{
		// printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		new_x += SPEED * sin((mlx->player->look + 90) * M_PI / 180);
		new_y += SPEED * cos((mlx->player->look + 90) * M_PI / 180);
	}
	else if (key == 97 || key == 65363)
	{
		// printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		new_x -= SPEED * sin((mlx->player->look + 90) * M_PI / 180);
		new_y -= SPEED * cos((mlx->player->look + 90) * M_PI / 180);
	}
	else if (key == 113)
	{
		// printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->look += 5;
	}
	else if (key == 101)
	{
		// printf("%f %f\n", mlx->player->pos_x, mlx->player->pos_y);
		mlx->player->look -= 5;
	}
	if (is_valid_move_y(mlx, new_y))
		mlx->player->pos_y = new_y;
	if (is_valid_move_x(mlx, new_x))
		mlx->player->pos_x = new_x;
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