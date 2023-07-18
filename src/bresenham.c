/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:27:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/18 13:27:30 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	bresenham_cub(t_mlx mlx, float dest_x, float dest_y, int color)
{
	int	dx;
	int	dy;
	int	r[3];
	int	x;
	int	y;

	x = mlx.player->pos_x;
	y = mlx.player->pos_y;
	dx = (int)dest_x - (int)x;
	dy = (int) dest_y - (int)y;
	if (dx > 0)
	{
		if (dy > 0)
		{
			if (dx >= dy)/*IT WORK*/
			{
				r[0] = dx;
				dx *= 2;
				dy *= 2;
				while (1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if ((int)x++ >= (int)dest_x /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0]=r[0] - dy;
					if (r[0] < 0)
					 {
						y++;
						r[0] += dx;
					 }
				}
			}
			else if (dx <= dy)/*IT WORK*/
			{
				r[0] = dy;
				dx *= 2;
				dy *= 2;
				while (1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if (y++ >= (int)dest_y /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0] -= dx;
					if (r[0] < 0)
					 {
						x++;
						r[0] += dy;
					 }
				}
			}
		}
		else if (dy < 0) /*IT WORK*/
		{
			if (dx < -1 * dy)
			{
				r[0] = dy;
				dx *= 2;
				dy *= 2;
				while(1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if (y-- <= dest_y /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0]=r[0] - dx;
					if (r[0] < 0)
					{
						x++;
						r[0] -= dy;
					}
				}
			}
			else if (dx >= -dy) /*IT WORK*/
			{
				r[0] = dx;
				dx *= 2;
				dy *= 2;
				while(1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if (x++ >= dest_x /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0]=r[0] + dy;
					if (r[0] < 0)
					{
						y--;
						r[0] += dx;
					}
				}
			}
		}
		else /*IT WORK*/
		{
			while (x++ <= dest_x)
				my_mlx_pixel_put(&mlx, x, y, color);
		}
	}
	else if (dx < 0)
	{
		if (dy > 0)
		{
			if (-dx >= dy) /*IT WORK*/
			{
				r[0] = dx;
				dx *= 2;
				dy *= 2;
				while(1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if (x-- <= (int)dest_x /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0] = r[0] + dy;
					if (r[0] >= 0)
					{
						y++;
						r[0] += dx;
					}
				}
			}
			else /*IT WORK*/
			{
				r[0] = dy;
				dx *= 2;
				dy *= 2;
				while(1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if (y++ >= (int)dest_y /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0] = r[0] + dx;
					if (r[0] <= 0)
					{
						x--;
						r[0] += dy;
					}
				}
			}
		}
		else if (dy < 0)
		{
			if (dx > dy) /*IT WORK*/
			{
				r[0] = dy;
				dx *= 2;
				dy *= 2;
				while (1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if (y-- <= dest_y /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0] = r[0] + dx;
					if (r[0] < 0)
					{
						x--;
						r[0] -= dy;
					}
				}
			}
			else /*IT WORK*/
			{
				r[0] = dx;
				dx *= 2;
				dy *= 2;
				while (1)
				{
					my_mlx_pixel_put(&mlx, x, y, color);
					if (x-- <= dest_x /*|| x >= dest_x || y >= dest_y*/)
						break ;
					r[0] = r[0] - dy;
					if (r[0] >= 0)
					{
						y--;
						r[0] += dx;
					}
				}
			}
		}
		else
		{
			while(x-- >= dest_x)
				my_mlx_pixel_put(&mlx, x, y, color);
		}	}
	else
	{
		if (dy > 0)
		{
			while(y++ <= dest_y)
				my_mlx_pixel_put(&mlx, x, y, color);
		}
		else if (dy < 0)
		{
			while(y-- >= dest_y)
				my_mlx_pixel_put(&mlx, x, y, color);
		}
	}
}

// void	bresenham_cu2b(t_mlx mlx, float dest_x, float dest_y, int color)
// {
// 	int		x;
// 	int		y;
// 	int		dx;
// 	int		dy;
// 	float	rationel[3];

// 	(void)color;

// 	dy = dest_y - mlx.player->pos_y;
// 	if (dy == 0)
// 		dy = 1;
// 	dx = dest_x - mlx.player->pos_x;
// 	y = (int)mlx.player->pos_y;
// 	rationel[0] = -dx;
// 	rationel[1] = dy * 2;
// 	printf("Payer : %f | %f dx = %i dy = %i, rationel 0 = %f rationel 1 : %f\n", mlx.player->pos_x, mlx.player->pos_y, dx, dy, rationel[0], rationel[1]);
// 	rationel[2] = -dx * 2;
// 	x = (int)mlx.player->pos_x;
// 	while (x++ < (int)dest_x)
// 	{
// 		my_mlx_pixel_put(&mlx, x, y, UINT32_MAX);
// 		// rationel[0] = rationel[0] + rationel[1];
// 		if (rationel[0] + rationel[1] >= 0)
// 		{
// 			y++;
// 			rationel[0] = rationel [0] + rationel[2];
// 		}
// 	}
// }








// void	bresenham_cub4(t_mlx mlx, float dest_x, float dest_y, int color)
// {
// 	int	dx;
// 	int	dy;
// 	int	err;
// 	int	e2;
// 	int	s[2];
// 	int	x;
// 	int	y;

// 	s[0] = 2 * (mlx.player->pos_x < dest_x) - 1;
// 	s[1] = 2 * (mlx.player->pos_y < dest_y) - 1;
// 	x = mlx.player->pos_x;
// 	y = mlx.player->pos_y;
// 	dx = (int)dest_x - (int)x;
// 	dy = (int) dest_y - (int)y;
// 	err = dx;
// 		printf("in\n");
// 	while (x != dest_x || y != dest_y)
// 	{
// 		if (x && x < (*mlx.wall.east_height * 8) && y && y < (*mlx.wall.east_lenth * 8))
// 			my_mlx_pixel_put(&mlx, x, y, color);
// 		e2 = 2 * err;
// 		if (e2 >= dy)
// 		{
// 			err +=dy;
// 			x += s[1];
// 		}
// 		if (e2 <= dx)
// 		{
// 			err +=dx;
// 			y += s[1];
// 		}
// 	}
// 	printf("out\n");
// }

// void	draw_line(t_vars *vars, t_line ln, t_color color);
// {

	
	
// 	t_vec2i	d;
// 	t_vec2i	s;
// 	int		err;
// 	int		e2;

// 	err = d.x + d.y;
// 	while (ln.from.x != ln.to.x || ln.from.y != ln.to.y)
// 	{
// 		if (ln.from.x >= 0 && ln.from.x < vars->scene->render->width
// 			&& ln.from.y >= 0 && ln.from.y < vars->scene->render->height)
// 			vars->set_pixel(vars->camera->render, ln.from.x, ln.from.y, color);
// 		e2 = 2 * err;
// 		if (e2 >= d.y)
// 		{
// 			err += d.y;
// 			ln.from.x += s.x;
// 		}
// 		if (e2 <= d.x)
// 		{
// 			err += d.x;
// 			ln.from.y += s.y;
// 		}
// 	}
// }