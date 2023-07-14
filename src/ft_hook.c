/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:04:32 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/14 10:46:32 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_hook(int key, t_player *player)
{
	if (key == 65307)
		exit(0);
	else if (key == 115 || key == 65364)
	{
		printf("%f %f\n", player->pos_x, player->pos_y);
		player->pos_y += 9;
	}
	else if (key == 119 || key == 65362)
	{
		printf("%f %f\n", player->pos_x, player->pos_y);
		player->pos_y -= 9;
	}
	else if (key == 97 || key == 65361)
	{
		printf("%f %f\n", player->pos_x, player->pos_y);
		player->pos_x -= 9;
	}
	else if (key == 100 || key == 65363)
	{
		printf("%f %f\n", player->pos_x, player->pos_y);
		player->pos_x += 9;
	}
	else if (key == 113)
	{
		printf("%f %f\n", player->pos_x, player->pos_y);
		player->look -= 5;
	}
	else if (key == 101)
	{
		printf("%f %f\n", player->pos_x, player->pos_y);
		player->look += 5;
	}
	if (player->look <= 0)
		player->look += 360;
	if (player->look >= 360)
		player->look -= 360;
	return (0);
}


// left_arrow  65363
// right_arrow 65361
// up_arrow 65362
// down_arrow 65364
// W 119
// A 97
// S 115
// D 100
// escape 65307
// Q  113
// E 101