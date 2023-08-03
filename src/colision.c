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

int	is_valid_move_x(t_mlx *mlx, float new_x)
{
	size_t		x;
	size_t		y;
	char		c;

	x = (int)floor(new_x * 0.02);
	y = (int)floor(mlx->player->pos_y * 0.02) + 1;
	if (y > mlx->map->x_lenth || x > mlx->map->y_lenth)
		return (0);
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}

int	is_valid_move_y(t_mlx *mlx, float new_y)
{
	size_t		x;
	size_t		y;
	char		c;

	x = (int)floor(mlx->player->pos_x * 0.02);
	y = (int)floor(new_y * 0.02) + 1;
	if (y > mlx->map->x_lenth || x > mlx->map->y_lenth)
		return (0);
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}

int	is_valid_move(t_mlx *mlx, float new_y, float new_x)
{
	size_t		x;
	size_t		y;
	char		c;

	x = floor(new_x * 0.02);
	y = floor(new_y * 0.02) + 1;
	if (y > mlx->map->x_lenth || x > mlx->map->y_lenth)
		return (0);
	c = mlx->map->map[y][x];
	if (c == '1')
		return (0);
	return (1);
}
