/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:02:02 by mbrement          #+#    #+#             */
/*   Updated: 2023/08/03 23:18:36 by mbrement         ###   ########lyon.fr   */
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

	y = 1;
	mlx->org = malloc(sizeof(t_data));
	mlx->org->img = mlx_new_image(mlx->mlx_init_ptr, WIN_W, WIN_H);
	mlx->org->addr = mlx_get_data_addr(mlx->org->img, &mlx->org->bits_per_pixel, &mlx->org->line_length, &mlx->org->endian);
	if (map.map && map.map[1])
		px_by_elem_x = WIN_W / (ft_strlen(map.map[1]) - 1);
	else
	 	return ;
	px_by_elem_y = -1;
	while (map.map[++px_by_elem_y])
		;
	mlx->map->y_lenth = ft_strlen(map.map[1]) - 1;
	mlx->map->x_lenth = px_by_elem_y - 2;
	printf("RANGE = y = %zu | x = %zu\n", mlx->map->y_lenth, mlx->map->x_lenth);
	printf("%s\n", map.map[1]);
	px_by_elem_y = WIN_H / (px_by_elem_y - 2);
	mlx->org->pixel_to_mapx = px_by_elem_x;
	mlx->org->pixel_to_mapy = px_by_elem_y;
	while (map.map[y])
	{
		x = 0;
		while (map.map[y][x])
		{
			if (map.map[y][x] == '1')
				block_in_img(px_by_elem_x, px_by_elem_y, y - 1, x, *mlx);
			x++;
		}
		y++;
	}
	printf("coordonner x =%i, y = %i\n", locate_player_x(map.map), locate_player_y(map.map));
	mlx->player->pos_x = mlx->map->player_x * 50 * (px_by_elem_y) + 0.5 * px_by_elem_y ;
	mlx->player->pos_y = (mlx->map->player_y * 50 - 1) * (px_by_elem_x) + 0.5 * px_by_elem_x ;
}

static void	my_mlx_pixel_put2(t_mlx *mlx, int y, int x, unsigned int color)
{
	char	*dst;

	if (y > WIN_H || x > WIN_W || y < 0 || x < 0)
		return ;
	dst = mlx->org->addr + (y * mlx->org->line_length + x * 4);
	*(unsigned int *)dst = color;
}


void	block_in_img(size_t px_by_elem_y, size_t px_by_elem_x, int x, int y, t_mlx mlx)
{
	int	i;
	int	j;

	i = x;
	while (i != x + (int)px_by_elem_x + 1)
	{
		j = y;
		while (j != y + (int)px_by_elem_y + 1)
		{
			my_mlx_pixel_put2(&mlx, i + x * (int)px_by_elem_x, j + y * (int)px_by_elem_y, UINT32_MAX);
			j++;
		}
		i++;
	}
}
