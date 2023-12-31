/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:17:49 by ngennaro          #+#    #+#             */
/*   Updated: 2023/08/03 23:19:01 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_move_x(t_mlx *mlx, double new_x)
{
	long int		x;
	long int		y;
	char			c;

	if (new_x > mlx->player->pos_x)
		new_x += 0.1;
	else
		new_x -= 0.1;
	x = (int)floor(new_x);
	y = (int)floor(mlx->player->pos_y);
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}

int	is_valid_move_y(t_mlx *mlx, double new_y)
{
	long int		x;
	long int		y;
	char			c;

	if (new_y > mlx->player->pos_y)
		new_y += 0.1;
	else
		new_y -= 0.1;
	x = (int)floor(mlx->player->pos_x);
	y = (int)floor(new_y);
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}

int	is_valid_move(t_mlx *mlx, double new_x, double new_y)
{
	long int		x;
	long int		y;
	char			c;

	x = floor(new_x);
	y = floor(new_y);
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}
