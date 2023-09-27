/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:46:55 by mbrement          #+#    #+#             */
/*   Updated: 2023/09/27 05:52:56 by kali             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_wall_data	get_data_wall(void *wall)
{
	int			*bits_py_px;
	int			*size_line;
	int			*endian;
	t_wall_data	data;

	bits_py_px = malloc(sizeof (int));
	size_line = malloc(sizeof (int));
	endian = malloc(sizeof (int));
	data.addr = mlx_get_data_addr(wall, bits_py_px, size_line, endian);
	data.size_line = size_line;
	data.bits_py_px = bits_py_px;
	data.endian = endian;
	return (data);
}

void	data_wall(t_wall *wall)
{
	wall->east_data = get_data_wall(wall->east);
	wall->north_data = get_data_wall(wall->north);
	wall->west_data = get_data_wall(wall->west);
	wall->south_data = get_data_wall(wall->south);
}
