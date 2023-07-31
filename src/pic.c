/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:05:52 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/31 17:52:34 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

;	
void	my_mlx_pixel_put2(char *addr, int line_lenth, int x, int y, unsigned int color)
{
	char	*dst;

	if (y > WIN_H || x > WIN_W || y < 0 || x < 0)
		return ;
	dst = addr + (y * line_lenth + x * 4);
	*(unsigned int *)dst = color;
}

unsigned int get_color(void *img_ptr, int x, int y, t_mlx *mlx)
{
	char	*dst;
	char	*addr;
	int		bits_py_px;
	int		size_line;
	int		endian;

	(void)mlx;
	x = ((float)(*mlx->wall.east_height *  x) / WIN_W);
	y = ((float)(*mlx->wall.east_lenth * y) / WIN_H);
	// addr = malloc(sizeof(char*));
	addr = mlx_get_data_addr(img_ptr, &bits_py_px, &size_line, &endian);
	dst = addr + (y * size_line + x * 4);
	// if (x > *mlx->wall.east_lenth || y > *mlx->wall.east_height || y < 0 || x < 0)
		// return (UINT32_MAX);
	// nfree((void**)&addr);
	return(*(unsigned int*)dst);


	
}

void	road_to_wall(t_mlx *mlx, int y, int x, float angle)
{
	void *init_tmp;
	void *win_tmp;
	void *img_tmp;
	char *addr_tmp;
	int	tmp1;
	int	tmp2;
	int	tmp3;
	size_t	tmp;

	(void)x;
	(void)y;
	(void)angle;
	(void)mlx;
	img_tmp = malloc(sizeof(void*));

	init_tmp = mlx_init();
	win_tmp = mlx_new_window(init_tmp, WIN_W, WIN_H, "test");
	img_tmp = mlx_new_image(init_tmp, WIN_W, WIN_H);
	addr_tmp = mlx_get_data_addr(img_tmp, &tmp1, &tmp2, &tmp3);
	tmp = 0;
	while(tmp++ < 1500)
		{
			tmp3 = 0;
			while(tmp3++ < 750)
			{
				my_mlx_pixel_put2(addr_tmp, tmp2, tmp, tmp3, get_color(mlx->wall.east, tmp, tmp3,  mlx)); 
			}
		}
	mlx_put_image_to_window(init_tmp, win_tmp, img_tmp, 0, 0);
}
