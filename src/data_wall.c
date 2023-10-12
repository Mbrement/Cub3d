/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:46:55 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/12 19:08:16 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_data(int *bits_py_px, int *size_line, int *endian)
{
	nfree((void **)&bits_py_px);
	nfree((void **)&size_line);
	nfree((void **)&endian);
}

static t_wall_data	get_data_wall(void *wall)
{
	int			*bits_py_px;
	int			*size_line;
	int			*endian;
	t_wall_data	data;

	bits_py_px = malloc(sizeof (int));
	size_line = malloc(sizeof (int));
	endian = malloc(sizeof (int));
	if (!endian || !size_line || !bits_py_px)
	{
		free_data(bits_py_px, size_line, endian);
		data.addr = NULL;
		return (data);
	}
	data.addr = mlx_get_data_addr(wall, bits_py_px, size_line, endian);
	if (!data.addr)
	{
		free_data(bits_py_px, size_line, endian);
		return (data);
	}
	data.size_line = size_line;
	data.bits_py_px = bits_py_px;
	data.endian = endian;
	return (data);
}

void	data_wall(t_wall *wall, t_mlx *mlx)
{
	wall->east_data = get_data_wall(wall->east);
	wall->north_data = get_data_wall(wall->north);
	wall->west_data = get_data_wall(wall->west);
	wall->south_data = get_data_wall(wall->south);
	if (!wall->east_data.addr || !wall->east_data.addr || \
		!wall->east_data.addr || !wall->east_data.addr)
	{
		mlx->wall = wall;
		mlx->player = NULL;
		end_of_prog_mlx(mlx);
	}
}
