/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:33:01 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/12 16:34:20 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_rotate(t_mlx *mlx)
{
	if (mlx->player->turn_left == 1 && nbr_of_key(mlx) == 0)
		mlx->player->look -= 3;
	else if (mlx->player->turn_left == 1)
		mlx->player->look -= 2;
	if (mlx->player->turn_right == 1 && nbr_of_key(mlx) == 0)
		mlx->player->look += 3;
	else if (mlx->player->turn_right == 1)
		mlx->player->look += 2;
	if (mlx->player->look < 0)
		mlx->player->look += 360;
	else if (mlx->player->look >= 360)
		mlx->player->look -= 360;
}

void	ft_direction(t_mlx *mlx, double *new_x, double *new_y, double *speed)
{
	static double	rad = (M_PI / 180);

	if (mlx->player->move_up == 1)
	{
		*new_y += *speed * sin(mlx->player->look * rad);
		*new_x += *speed * cos(mlx->player->look * rad);
	}
	if (mlx->player->move_down == 1)
	{
		*new_y -= *speed * sin(mlx->player->look * rad);
		*new_x -= *speed * cos(mlx->player->look * rad);
	}
	if (mlx->player->move_right == 1)
	{
		*new_x += *speed * sin(mlx->player->look * rad);
		*new_y -= *speed * cos(mlx->player->look * rad);
	}
	if (mlx->player->move_left == 1)
	{
		*new_x -= *speed * sin(mlx->player->look * rad);
		*new_y += *speed * cos(mlx->player->look * rad);
	}
}

int	ft_move(t_mlx *mlx)
{
	double			new_x;
	double			new_y;
	double			speed;

	new_x = mlx->player->pos_x;
	new_y = mlx->player->pos_y;
	if (mlx->player->boost == 1)
		speed = SPEED * 2;
	else
		speed = SPEED;
	if (nbr_of_key(mlx) > 1)
		speed *= 0.75;
	ft_direction(mlx, &new_x, &new_y, &speed);
	ft_rotate(mlx);
	if (is_valid_move_y(mlx, new_y))
		mlx->player->pos_y = new_y;
	if (is_valid_move_x(mlx, new_x))
		mlx->player->pos_x = new_x;
	return (0);
}
