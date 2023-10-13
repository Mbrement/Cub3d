/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:49:44 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/13 10:50:03 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_walls(t_map *map)
{
	char	**tmp_map;
	int		x;
	int		y;

	tmp_map = dup_maps(map->map);
	if (!tmp_map)
		end_of_prog(*map, "Error\nMalloc error\n");
	x = locate_player_x(tmp_map);
	y = locate_player_y(tmp_map);
	tmp_map[y][x] = '*';
	if (!complete_map(tmp_map))
	{
		free_tab(tmp_map);
		end_of_prog(*map, "Error\nIncorrect map\n");
	}
	free_tab(tmp_map);
	return (1);
}
