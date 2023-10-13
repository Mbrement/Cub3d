/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:16:57 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/13 10:17:47 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	init_ray(t_ray *ray, double *offset_x, double *offset_y, t_mlx *mlx)
{
	double	angle_radiants;

	angle_radiants = mlx->player->look * M_PI / 180.;
	*offset_x = mlx->player->pos_x - (int)mlx->player->pos_x;
	*offset_y = mlx->player->pos_y - (int)mlx->player->pos_y;
	ft_prep_floor(mlx);
	angle_radiants = mlx->player->look * M_PI / 180.;
	ray->dirx = cos(angle_radiants);
	ray->diry = sin(angle_radiants);
	ray->planx = -ray->diry;
	ray->plany = ray->dirx;
	return (angle_radiants);
}

void	reset_ray(t_mlx *mlx, t_ray *ray, int i)
{
	ray->pos_x = (int)mlx->player->pos_x;
	ray->pos_y = (int)mlx->player->pos_y;
	ray->camerax = 2 * i / (double)WIN_W - 1;
	ray->raydirx = ray->dirx + (ray->planx * ray->camerax);
	ray->raydiry = ray->diry + ray->plany * ray->camerax;
	ray->deltadistx = fabs(1 / ray->raydirx);
	ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
}

void	set_dist(t_ray *ray, double offset_x, double offset_y)
{
	if (ray->raydirx < 0)
	{
		ray->sidedistx = offset_x * ray->deltadistx;
		ray->stepx = -1;
	}
	else
	{
		ray->sidedistx = (1. - offset_x) * ray->deltadistx;
		ray->stepx = 1;
	}
	if (ray->raydiry < 0)
	{
		ray->sidedisty = offset_y * ray->deltadisty;
		ray->stepy = -1;
	}
	else
	{
		ray->sidedisty = (1. - offset_y) * ray->deltadisty;
		ray->stepy = 1;
	}
}
