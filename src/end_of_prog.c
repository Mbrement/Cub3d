/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:38:25 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/13 10:21:22 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	end_of_prog(t_map map, char *err_msg)
{
	ft_putstr_fd(err_msg, 1);
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
	if (mlx->wall->north_data.addr)
	{
		nfree ((void **)&mlx->wall->north_data.bits_py_px);
		nfree ((void **)&mlx->wall->north_data.endian);
		nfree ((void **)&mlx->wall->north_data.size_line);
	}
	if (mlx->wall->west_data.addr)
	{
		nfree ((void **)&mlx->wall->west_data.bits_py_px);
		nfree ((void **)&mlx->wall->west_data.endian);
		nfree ((void **)&mlx->wall->west_data.size_line);
	}
	if (mlx->wall->south_data.addr)
	{
		nfree ((void **)&mlx->wall->south_data.bits_py_px);
		nfree ((void **)&mlx->wall->south_data.endian);
		nfree ((void **)&mlx->wall->south_data.size_line);
	}
	if (mlx->wall->east_data.addr)
	{
		nfree ((void **)&mlx->wall->east_data.bits_py_px);
		nfree ((void **)&mlx->wall->east_data.endian);
		nfree ((void **)&mlx->wall->east_data.size_line);
	}
}

static void	free_wall(t_mlx *mlx)
{
	if (mlx->wall)
	{
		if (mlx->wall->north)
			mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->north);
		if (mlx->wall->east)
			mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->east);
		if (mlx->wall->west)
			mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->west);
		if (mlx->wall->south)
			mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->south);
		if (mlx->wall->north && mlx->wall->east \
			&& mlx->wall->west && mlx->wall->south)
			free_wall_data(mlx);
	}
}

void	end_of_prog_mlx(t_mlx *mlx)
{
	if (mlx->mlx_init_ptr)
	{
		free_wall(mlx);
		nfree((void **)&mlx->player);
		if (mlx->mlx_win_ptr)
			mlx_destroy_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr);
		mlx_destroy_display(mlx->mlx_init_ptr);
	}
	nfree((void **)&mlx->wall);
	nfree((void **)&mlx->mlx_init_ptr);
	nfree((void **)&mlx->data);
	end_of_prog_no_exit(*mlx->map);
	nfree((void **)&mlx);
	exit(0);
}
