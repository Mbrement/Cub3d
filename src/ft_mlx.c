/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:59:36 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/13 16:46:48 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_mlx(t_map map)
{
	void	*mlx_init_ptr;
	void	*mlx_win_ptr;
	void	*mlx_img_ptr;
	int		*a;
	int		*b;

	(void)map;
	a = malloc(sizeof(int *));
	b = malloc(sizeof(int *));
	mlx_init_ptr = mlx_init();
	if (!mlx_init_ptr)
	{
		printf("Mlx couldn't init\n");
		exit(1);
	}
	mlx_img_ptr = mlx_xpm_file_to_image(mlx_init_ptr, "./img/bny1689166835.xpm", a, b);
	printf("%p\n", mlx_img_ptr);
	mlx_win_ptr = mlx_new_window(mlx_init_ptr, *a * 2, *b * 2, "cub3d");
	if (!mlx_win_ptr)
	{
		printf("Mlx create the window\n");
		exit(1);
	}
	mlx_put_image_to_window(mlx_init_ptr, mlx_win_ptr, mlx_img_ptr, 0, 0);
	mlx_put_image_to_window(mlx_init_ptr, mlx_win_ptr, mlx_img_ptr, *a, 0);
	mlx_put_image_to_window(mlx_init_ptr, mlx_win_ptr, mlx_img_ptr, *a, *b);
	mlx_put_image_to_window(mlx_init_ptr, mlx_win_ptr, mlx_img_ptr, 0, *b);
	sleep(15);
	mlx_destroy_image(mlx_init_ptr, mlx_img_ptr);
	mlx_destroy_window(mlx_init_ptr, mlx_win_ptr);
	mlx_destroy_display(mlx_init_ptr);
	free(mlx_init_ptr);
	nfree((void **)&a);
	nfree((void **)&b);
}
