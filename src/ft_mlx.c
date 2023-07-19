/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/19 11:11:04 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stddef.h>

void	ray(t_mlx mlx, t_player player, int rgb);
t_wall	put_img_in_wall(t_map map, t_mlx mlx);
void	create_map(t_mlx mlx, t_map map);
void ft_fuse_pic(t_mlx mlx);

void	ft_mlx(t_map map)
{
	t_mlx	*mlx;
	t_data	*data;

	data = malloc(sizeof(t_data));
	mlx = malloc(sizeof(t_mlx));
	(void)map;
	mlx->data = data;
	mlx->mlx_init_ptr = mlx_init();
	if (!mlx->mlx_init_ptr)
	{
		printf("Mlx couldn't init\n");
		exit(1);
	}
	mlx->wall = put_img_in_wall(map, *mlx);
	mlx->mlx_win_ptr = mlx_new_window(mlx->mlx_init_ptr, WIN_W, WIN_H, "cub3d");
	if (!mlx->mlx_win_ptr)
	{
		printf("Mlx create the window\n");
		exit(1);
	}
	create_map(*mlx, map);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.north);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.east);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.south);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall.west);
	mlx_destroy_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr);
	mlx_destroy_display(mlx->mlx_init_ptr);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	if (y > WIN_H || x > WIN_W || y < 0 || x < 0)
		return ;
	dst = mlx->data->addr + (y * mlx->data->line_length + x * (mlx->data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int	ft_dmg_control(int key, t_mlx *mlx)
{
	mlx->data->img = mlx_new_image(mlx->mlx_init_ptr, WIN_W, WIN_H);
	mlx->data->addr = mlx_get_data_addr(mlx->data->img, &mlx->data->bits_per_pixel, &mlx->data->line_length, &mlx->data->endian);
	printf ("addr %p, bpp %i, line lenth %i, endiant : %i\n", mlx->data->addr, mlx->data->bits_per_pixel, mlx->data->line_length, mlx->data->endian);
	put_player(*mlx, *mlx->player, 0);
	ft_hook(key, mlx);
	ray (*mlx, *mlx->player, 0xFF0000);
	ft_fuse_pic(*mlx);
	// mlx_put_image_to_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr, mlx->org->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr, mlx->data->img, 0, 0);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->data->img);
	return (1);
}

//debug
int	ft_exit(int i)
{
	exit(i);
	return(0);
}
//endofdebug
void	player_get_look(t_mlx *mlx, t_map map)
{
	char	c;

	c = map.map[locate_player_y(map.map)][locate_player_x(map.map)];
	mlx->player->look = 0;
	if (c == 'W')
		mlx->player->look = 270;
	else if (c == 'E')
		mlx->player->look = 90;
	else if (c == 'S')
		mlx->player->look = 0;
	else if (c == 'N')
		mlx->player->look = 180;
	else
	{
	 	printf("didn't find orientation, set it to 0\n");
		mlx->player->look = 0;
	}
}

void	create_map(t_mlx mlx, t_map map)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	mlx.player = player;
	player_get_look(&mlx, map);
	map_img(&mlx, map);
	put_player(mlx, *player, UINT32_MAX);
	mlx_hook(mlx.mlx_win_ptr, 17, 1L << 0, ft_exit, NULL);
	mlx_key_hook(mlx.mlx_win_ptr, ft_dmg_control, &mlx);
	mlx_loop(mlx.mlx_init_ptr);
}

t_wall	put_img_in_wall(t_map map, t_mlx mlx)
{
	t_wall	wall;

	wall.north = malloc(sizeof(void *));
	wall.north_height = malloc(sizeof(int *));
	wall.north_lenth = malloc(sizeof (int *));
	wall.south = malloc(sizeof(void *));
	wall.south_height = malloc(sizeof (int *));
	wall.south_lenth = malloc(sizeof (int *));
	wall.east = malloc(sizeof(void *));
	wall.east_height = malloc(sizeof (int *));
	wall.east_lenth = malloc(sizeof (int *));
	wall.west = malloc(sizeof(void *));
	wall.west_height = malloc(sizeof(int *));
	wall.west_lenth = malloc(sizeof (int *));
	wall.north = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.north_file, wall.north_height, wall.north_lenth);
	wall.east = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.south_file, wall.south_height, wall.south_lenth);
	wall.west = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.east_file, wall.east_height, wall.east_lenth);
	wall.south = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.west_file, wall.west_height, wall.west_lenth);
	return (wall);
}

void ft_fuse_pic(t_mlx mlx)
{
	char	*dst;
	int		x;
	int		y;
	unsigned int color;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			dst = mlx.data->addr + (y * mlx.data->line_length + x * (mlx.data->bits_per_pixel / 8));
			if (*(unsigned int *)(mlx.data->addr + (y * mlx.data->line_length + x * (mlx.data->bits_per_pixel / 8))))
				color = *(unsigned int *)(mlx.data->addr + (y * mlx.data->line_length + x * (mlx.data->bits_per_pixel / 8)));
			else
			 	color = *(unsigned int *)(mlx.org->addr + (y * mlx.org->line_length + x * (mlx.org->bits_per_pixel / 8)));
			*(unsigned int *)dst = color;
			x++;
		}
	y++;
	}
}
