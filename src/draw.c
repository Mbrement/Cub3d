/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:31:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/10 09:32:10 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_draw_vertical_north(t_mlx *mlx, int screen_x, int *drawn, int x)
{
	int				tex_y;
	char			*tex_pixel_addr;
	unsigned int	tex_color;
	int				y;

	y = drawn[0];
	while (y < drawn[1])
	{
		tex_y = ((int)((y - drawn[0]) * (mlx->wall->north_lenth))
				/ (double)(drawn[1] - drawn[0]));
		tex_pixel_addr = mlx->wall->north_data.addr
			+ (tex_y * *mlx->wall->north_data.size_line + x
				* (*mlx->wall->north_data.bits_py_px / 8));
		tex_color = *((int *)tex_pixel_addr);
		my_mlx_pixel_put(mlx, screen_x, y, tex_color);
		y++;
	}
}

void	ft_draw_vertical_south(t_mlx *mlx, int screen_x, int *drawn, int x)
{
	int				tex_y;
	char			*tex_pixel_addr;
	unsigned int	tex_color;
	int				y;

	y = drawn[0];
	while (y < drawn[1])
	{
		tex_y = ((int)((y - drawn[0]) * (mlx->wall->south_lenth))
				/ (double)(drawn[1] - drawn[0]));
		tex_pixel_addr = mlx->wall->south_data.addr
			+ (tex_y * *mlx->wall->south_data.size_line + x
				* (*mlx->wall->south_data.bits_py_px / 8));
		tex_color = *((int *)tex_pixel_addr);
		my_mlx_pixel_put(mlx, screen_x, y, tex_color);
		y++;
	}
}

void	ft_draw_vertical_west(t_mlx *mlx, int screen_x, int *drawn, int x)
{
	int				tex_y;
	char			*tex_pixel_addr;
	unsigned int	tex_color;
	int				y;

	y = drawn[0];
	while (y < drawn[1])
	{
		tex_y = ((int)((y - drawn[0]) * (mlx->wall->west_lenth))
				/ (double)(drawn[1] - drawn[0]));
		tex_pixel_addr = mlx->wall->west_data.addr
			+ (tex_y * *mlx->wall->west_data.size_line + x
				* (*mlx->wall->west_data.bits_py_px / 8));
		tex_color = *((int *)tex_pixel_addr);
		my_mlx_pixel_put(mlx, screen_x, y, tex_color);
		y++;
	}
}

void	ft_draw_vertical_east(t_mlx *mlx, int screen_x, int *drawn, int x)
{
	int				tex_y;
	char			*tex_pixel_addr;
	unsigned int	tex_color;
	int				y;

	y = drawn[0];
	while (y < drawn[1])
	{
		tex_y = ((int)((y - drawn[0]) * (mlx->wall->east_lenth))
				/ (double)(drawn[1] - drawn[0]));
		tex_pixel_addr = mlx->wall->east_data.addr
			+ (tex_y * *mlx->wall->east_data.size_line + x
				* (*mlx->wall->east_data.bits_py_px / 8));
		tex_color = *((int *)tex_pixel_addr);
		my_mlx_pixel_put(mlx, screen_x, y, tex_color);
		y++;
	}
}

void	ft_prep_floor(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_H / 2)
	{
		x = -1;
		while (++x < WIN_W)
		{
			my_mlx_pixel_put(mlx, x, y, mlx->map->celing_color);
		}
	}
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			my_mlx_pixel_put(mlx, x, y, mlx->map->floor_color);
		}
	}
}