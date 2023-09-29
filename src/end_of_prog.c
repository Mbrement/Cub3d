/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:38:25 by mbrement          #+#    #+#             */
/*   Updated: 2023/09/29 13:48:24 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	end_of_prog_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->north);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->east);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->west);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->wall->south);
	nfree((void **)&mlx->wall);
	mlx_destroy_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr);
	mlx_destroy_display(mlx->mlx_init_ptr);
	nfree((void **)&mlx->mlx_init_ptr);
	nfree((void **)&mlx->data);
	end_of_prog_no_exit(*mlx->map);
	nfree((void **)&mlx);
	exit(0);
}
