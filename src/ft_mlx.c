/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/12 12:19:45 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_mlx(t_map map)
{
	void	*mlx_init_ptr;
	void	*mlx_win_ptr;

	(void)map;
	mlx_init_ptr = mlx_init();
	if (!mlx_init_ptr)
	{
		printf("Mlx couldn't init\n");
		exit(1);
	}
	mlx_win_ptr = mlx_new_window(mlx_init_ptr, WIN_H, WIN_H, "cub3d");
	if (!mlx_win_ptr)
	{
		printf("Mlx create the window\n");
		exit(1);
	}
	mlx_destroy_window(mlx_init_ptr, mlx_win_ptr);
	mlx_destroy_display(mlx_init_ptr);
}
