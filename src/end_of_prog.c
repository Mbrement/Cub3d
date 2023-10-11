/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:38:25 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/11 15:51:58 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_exit(int i, t_mlx *mlx)
{
	end_of_prog_mlx(mlx);
	return (i);
}

void	end_of_prog(t_map map)
{
	if (map.north_found && map.north > 2)
		close(map.north);
	if (map.east_found && map.east > 2)
		close(map.east);
	if (map.south_found && map.south > 2)
		close(map.south);
	if (map.west_found && map.west > 2)
		close(map.west);
	nfree((void **)&map.north_file);
	nfree((void **)&map.south_file);
	nfree((void **)&map.east_file);
	nfree((void **)&map.west_file);
	free_tab(map.map);
	exit(1);
}

void	end_of_prog_no_exit(t_map map)
{
	if (map.north_found && map.north > 2)
		close(map.north);
	if (map.east_found && map.east > 2)
		close(map.east);
	if (map.south_found && map.south > 2)
		close(map.south);
	if (map.west_found && map.west > 2)
		close(map.west);
	nfree((void **)&map.north_file);
	nfree((void **)&map.south_file);
	nfree((void **)&map.east_file);
	nfree((void **)&map.west_file);
	free_tab(map.map);
}

static void	free_wall_data(t_mlx *mlx)
{
	nfree ((void **)&mlx->wall->north_data.bits_py_px);
	nfree ((void **)&mlx->wall->east_data.bits_py_px);
	nfree ((void **)&mlx->wall->west_data.bits_py_px);
	nfree ((void **)&mlx->wall->south_data.bits_py_px);
	nfree ((void **)&mlx->wall->north_data.endian);
	nfree ((void **)&mlx->wall->east_data.endian);
	nfree ((void **)&mlx->wall->west_data.endian);
	nfree ((void **)&mlx->wall->south_data.endian);
	nfree ((void **)&mlx->wall->north_data.size_line);
	nfree ((void **)&mlx->wall->east_data.size_line);
	nfree ((void **)&mlx->wall->west_data.size_line);
	nfree ((void **)&mlx->wall->south_data.size_line);
}

void	end_of_prog_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->north);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->east);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->west);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->south);
	free_wall_data(mlx);
	nfree((void **)&mlx->wall);
	mlx_destroy_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr);
	mlx_destroy_display(mlx->mlx_init_ptr);
	nfree((void **)&mlx->mlx_init_ptr);
	nfree((void **)&mlx->data);
	nfree((void **)&mlx->player);
	end_of_prog_no_exit(*mlx->map);
	nfree((void **)&mlx);
	exit(0);
}
