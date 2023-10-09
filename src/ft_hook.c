/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:04:32 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/09 15:58:28 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == 65307)
		end_of_prog_mlx(mlx);
	else if (key == 119 || key == 65362)
		mlx->player->move_up = 1;
	else if (key == 115 || key == 65364)
		mlx->player->move_down = 1;
	else if (key == 97 || key == 65361)
		mlx->player->move_left = 1;
	else if (key == 100 || key == 65363)
		mlx->player->move_right = 1;
	else if (key == 113)
		mlx->player->turn_left = 1;
	else if (key == 101)
		mlx->player->turn_right = 1;
	return (0);
}

int	key_released(int key, t_mlx *mlx)
{
	if (key == 119 || key == 65362)
		mlx->player->move_up = 0;
	else if (key == 115 || key == 65364)
		mlx->player->move_down = 0;
	else if (key == 97 || key == 65361)
		mlx->player->move_left = 0;
	else if (key == 100 || key == 65363)
		mlx->player->move_right = 0;
	else if (key == 113)
		mlx->player->turn_left = 0;
	else if (key == 101)
		mlx->player->turn_right = 0;
	return (0);
}

int	ft_move(t_mlx *mlx)
{
	double			new_x;
	double			new_y;
	static double	rad = (M_PI / 180);

	new_x = mlx->player->pos_x;
	new_y = mlx->player->pos_y;
	if (mlx->player->move_up == 1)
	{
		if (mlx->player->move_down == 1 || mlx->player->move_left == 1 || mlx->player->move_right == 1)
		{
			new_y += SPEED*0.75 * sin(mlx->player->look * rad);
			new_x += SPEED*0.75 * cos(mlx->player->look * rad);
		}
		else
		{
			new_y += SPEED * sin(mlx->player->look * rad);
			new_x += SPEED * cos(mlx->player->look * rad);
		}
	}
	if (mlx->player->move_down == 1)
	{
		if (mlx->player->move_up == 1 || mlx->player->move_left == 1 || mlx->player->move_right == 1)
		{
			new_y -= SPEED*0.75 * sin(mlx->player->look * rad);
			new_x -= SPEED*0.75 * cos(mlx->player->look * rad);
		}
		else
		{
			new_y -= SPEED * sin(mlx->player->look * rad);
			new_x -= SPEED * cos(mlx->player->look * rad);
		}
	}
	if (mlx->player->move_left == 1)
	{
		if (mlx->player->move_up == 1 || mlx->player->move_down == 1 || mlx->player->move_right == 1)
		{
			new_x += SPEED*0.75 * sin(mlx->player->look * rad);
			new_y -= SPEED*0.75 * cos(mlx->player->look * rad);
		}
		else
		{
			new_x += SPEED * sin(mlx->player->look * rad);
			new_y -= SPEED * cos(mlx->player->look * rad);
		}
	}
	if (mlx->player->move_right == 1)
	{
		if (mlx->player->move_up == 1 || mlx->player->move_down == 1 || mlx->player->move_left == 1)
		{
			new_x -= SPEED*0.75 * sin(mlx->player->look * rad);
			new_y += SPEED*0.75 * cos(mlx->player->look * rad);
		}
		else
		{
			new_x -= SPEED * sin(mlx->player->look * rad);
			new_y += SPEED * cos(mlx->player->look * rad);
		}
	}
	if (mlx->player->turn_left == 1)
	{
		if (mlx->player->move_up == 1 || mlx->player->move_down == 1 || mlx->player->move_left == 1 || mlx->player->move_right == 1)
			mlx->player->look -= 2;
		else
			mlx->player->look -= 3;
	}
	if (mlx->player->turn_right == 1)
	{
		if (mlx->player->move_up == 1 || mlx->player->move_down == 1 || mlx->player->move_left == 1 || mlx->player->move_right == 1)
			mlx->player->look += 2;
		else
			mlx->player->look += 3;
	}
	if (is_valid_move_y(mlx, new_y))
		mlx->player->pos_y = new_y;
	if (is_valid_move_x(mlx, new_x))
		mlx->player->pos_x = new_x;
	if (mlx->player->look < 0)
		mlx->player->look += 360;
	else if (mlx->player->look >= 360)
		mlx->player->look -= 360;
	return (0);
}

int	handle_mouse(int x, int y, t_mlx *mlx)
{
	int			move;
	static int	midle_win_w = WIN_W * 0.5;
	static int	midle_win_h = WIN_H * 0.5;

	move = (int)((x - (int)(midle_win_w)) * 0.005);
	if (move == 0)
		return (0);
	mlx->player->look += move;
	(void)y;
	if (mlx->player->look > 360)
		mlx->player->look = 0;
	else if (mlx->player->look < 0)
		mlx->player->look = 360;
	mlx_mouse_move(mlx->mlx_init_ptr,
		mlx->mlx_win_ptr, midle_win_w, midle_win_h);
	return (0);
}
