/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/08/04 03:01:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray(t_mlx mlx, t_player player, int rgb);
t_wall	*put_img_in_wall(t_map map, t_mlx mlx);
void	init_game(t_mlx mlx, t_map map);
void	ft_fuse_pic(t_mlx mlx);


void	ft_mlx(t_map *map, t_mlx *mlx)
{

	if (!mlx)
		end_of_prog(*map);
	mlx->map = map;
	mlx->data = malloc(sizeof(t_data));
	if (!mlx->data)
		end_of_prog_mlx(mlx);
	mlx->mlx_init_ptr = mlx_init();
	if (!mlx->mlx_init_ptr)
	{
		printf("Mlx couldn't init\n");
		end_of_prog_mlx(mlx);
	}
	mlx->wall = put_img_in_wall(*map, *mlx);
	mlx->mlx_win_ptr = mlx_new_window(mlx->mlx_init_ptr, WIN_W, WIN_H, "cub3d");
	if (!mlx->mlx_win_ptr)
	{
		printf("Mlx create the window\n");
		end_of_prog_mlx(mlx);
	}
	init_game(*mlx, *map);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	if (y > WIN_H || x > WIN_W || y < 0 || x < 0)
		return ;
	dst = mlx->data->addr + (y * mlx->data->line_length + x * 4);
	*(unsigned int *)dst = color;
}
int	ft_dmg_control(int key, t_mlx *mlx)
{
	mlx->data->img = mlx_new_image(mlx->mlx_init_ptr, WIN_W, WIN_H);
	mlx->data->addr = mlx_get_data_addr(mlx->data->img, &mlx->data->bits_per_pixel, &mlx->data->line_length, &mlx->data->endian);
	// printf ("addr %p, bpp %i, line lenth %i, endiant : %i\n", mlx->data->addr, mlx->data->bits_per_pixel, mlx->data->line_length, mlx->data->endian);
	put_player(*mlx, *mlx->player, 0);
	ft_hook(key, mlx);
	ray (*mlx, *mlx->player, 0xFF0000);
	ft_fuse_pic(*mlx);
	// mlx_put_image_to_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr, mlx->org->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr, mlx->data->img, 0, 0);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->data->img);
	return (1);
}


int	ft_exit(int i, t_mlx *mlx)
{
	end_of_prog_mlx(mlx);
	return (i);
}

void	player_get_look(t_mlx *mlx, t_map map)
{
	char	c;

	c = map.map[locate_player_y(map.map)][locate_player_x(map.map)];
	if (c == 'W')
		mlx->player->look = 270;
	else if (c == 'E')
		mlx->player->look = 90;
	else if (c == 'S')
		mlx->player->look = 0;
	else if (c == 'N')
		mlx->player->look = 180;
}

void	init_game(t_mlx mlx, t_map map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	mlx.player = player;
	player_get_look(&mlx, map);
	player->pos_x = locate_player_x(map.map) * 50 + 25;
	player->pos_y = locate_player_y(map.map) * 50 + 25;
	mlx_hook(mlx.mlx_win_ptr, 17, 1L << 1, ft_exit, NULL);
	mlx_hook(mlx.mlx_win_ptr, 2, 1L << 0, ft_dmg_control, &mlx);
	mlx_loop(mlx.mlx_init_ptr);
}

t_wall	*put_img_in_wall(t_map map, t_mlx mlx)
{
	t_wall	*wall;

	// wall->north = malloc(sizeof(void *));
	wall = malloc(sizeof (t_wall));
	wall->north_height = malloc(sizeof(int *));
	wall->north_lenth = malloc(sizeof (int *));
	// wall->south = malloc(sizeof(void *));
	wall->south_height = malloc(sizeof (int *));
	wall->south_lenth = malloc(sizeof (int *));
	// wall->east = malloc(sizeof(void *));
	wall->east_height = malloc(sizeof (int *));
	wall->east_lenth = malloc(sizeof (int *));
	// wall->west = malloc(sizeof(void *));
	wall->west_height = malloc(sizeof(int *));
	wall->west_lenth = malloc(sizeof (int *));
	if (!wall->north_height || !wall->north_lenth || !wall->south_height
		|| !wall->south_lenth || !wall->east_height || !wall->east_lenth 
		|| !wall->west_height || !wall->west_lenth)
		end_of_prog_mlx(&mlx);
	wall->north = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.north_file, wall->north_height, wall->north_lenth);
	wall->east = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.south_file, wall->south_height, wall->south_lenth);
	wall->west = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.east_file, wall->east_height, wall->east_lenth);
	wall->south = mlx_xpm_file_to_image(mlx.mlx_init_ptr, \
		map.west_file, wall->west_height, wall->west_lenth);
	data_wall(wall);
	return (wall);
}

void ft_fuse_pic(t_mlx mlx)
{
	char			*dst;
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			dst = mlx.data->addr + (y * mlx.data->line_length + x * 4);
			if (*(unsigned int *)(mlx.data->addr + (y * mlx.data->line_length + x * 4)))
				color = *(unsigned int *)(mlx.data->addr + (y * mlx.data->line_length + x * 4));
			else
				color = *(unsigned int *)(mlx.org->addr + (y * mlx.org->line_length + x * 4));
			*(unsigned int *)dst = color;
			x++;
		}
	y++;
	}
}
