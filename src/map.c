/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:02:02 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/19 10:59:12 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	block_in_img(size_t px_by_elem_y, size_t px_by_elem_x, int x, int y, t_mlx mlx);

void	map_img(t_mlx *mlx, t_map map)
{
	size_t	px_by_elem_x;
	size_t	px_by_elem_y;
	size_t	x;
	size_t	y;

	x = 1;
	mlx->org = malloc(sizeof(t_data));
	mlx->org->img = mlx_new_image(mlx->mlx_init_ptr, WIN_W, WIN_H);
	mlx->org->addr = mlx_get_data_addr(mlx->org->img, &mlx->org->bits_per_pixel, &mlx->org->line_length, &mlx->org->endian);
	if (map.map && map.map[1])
		px_by_elem_y = WIN_W / (ft_strlen(map.map[1]) - 1);
	printf("RANGE = %zu | %zu\n", px_by_elem_y,  (ft_strlen(map.map[1])));
	px_by_elem_x = -1;
	while (map.map[++px_by_elem_x])
		;
	px_by_elem_x = WIN_H / (px_by_elem_x - 2);
	mlx->org->pixel_to_mapx = px_by_elem_y;
	mlx->org->pixel_to_mapy = px_by_elem_x;
	while (map.map[x])
	{
		y = 0;
		while (map.map[x][y])
		{
			if (map.map[x][y] == '1')
				block_in_img(px_by_elem_y, px_by_elem_x, x-1, y, *mlx);
			y++;
		}
		x++;
	}
	printf("coordonner x =%i, y = %i\n", locate_player_x(map.map), locate_player_y(map.map));
	mlx->player->pos_y = locate_player_x(map.map) * (px_by_elem_x) + 0.5 * px_by_elem_x ;
	mlx->player->pos_x = (locate_player_y(map.map) - 1) * (px_by_elem_y) + 0.5 * px_by_elem_y ;
}

static void	my_mlx_pixel_put2(t_mlx *mlx, int y, int x, unsigned int color)
{
	char	*dst;

	if (y > WIN_H || x > WIN_W || y < 0 || x < 0)
		return ;
	dst = mlx->org->addr + (y * mlx->org->line_length + x * (mlx->org->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


void	block_in_img(size_t px_by_elem_y, size_t px_by_elem_x, int x, int y, t_mlx mlx)
{
	int	i;
	int	j;

	i = x;
	while (i != x + (int)px_by_elem_x)
	{
		j = y;
		while (j != y + (int)px_by_elem_y)
		{
			my_mlx_pixel_put2(&mlx, i + x * (int)px_by_elem_x, j + y * (int)px_by_elem_y, UINT32_MAX);
			j++;
		}
		i++;
	}
}
