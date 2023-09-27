/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:04:32 by mbrement          #+#    #+#             */
/*   Updated: 2023/09/27 11:15:36 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

int	ft_hook(int key, t_mlx *mlx)
{
	float	new_x;
	float	new_y;
	float	rad;
	float	mvx;
	float	mvy;

	rad = (M_PI / 180);
	new_x = mlx->player->pos_x;
	new_y = mlx->player->pos_y;
	mvx = (SPEED);
	mvy = (SPEED);
	if (key == 65307)
		end_of_prog_mlx(mlx);
	else if (key == 119 || key == 65362)
	{
		new_x += mvx * cos(mlx->player->look * rad);
		new_y += mvy * sin(mlx->player->look * rad);
	}
	else if (key == 115 || key == 65364)
	{
		new_x -= mvx * cos(mlx->player->look * rad);
		new_y -= mvy * sin(mlx->player->look * rad);
	}
	else if (key == 97 || key == 65361)
	{
		new_x += mvx * sin(mlx->player->look * rad);
		new_y -= mvy * cos(mlx->player->look * rad);
	}
	else if (key == 100 || key == 65363)
	{
		new_x -= mvx * sin(mlx->player->look * rad);
		new_y += mvy * cos(mlx->player->look * rad);
	}
	else if (key == 113)
		mlx->player->look -= 5;
	else if (key == 101)
		mlx->player->look += 5;
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

int	handle_mouse_movement(int x, int y, t_mlx *mlx)
{
	int	move;

	move = (int)((x - (int)(WIN_W * 0.5)) * 0.005);
	if (move == 0)
		return (0);
	mlx->player->look += move;
	(void)y;
	if (mlx->player->look > 360)
		mlx->player->look = 0;
	else if (mlx->player->look < 0)
		mlx->player->look = 360;
	mlx_mouse_move(mlx->mlx_init_ptr, mlx->mlx_win_ptr, WIN_W * 0.5, WIN_H * 0.5);
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