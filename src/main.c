/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:33:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/12 11:27:23 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	death_map(t_map *map);
t_map	define_map(t_map map);

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	*mlx;

	if (argc != 2)
		return ((void)printf("Error\nWrong number of argument\n"), 1);
	map = define_map(map);
	map = check_file(argv[1], map);
	death_map(&map);
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		end_of_prog(map, "Error\nMalloc error\n");
	ft_mlx(&map, mlx);
	end_of_prog_mlx(mlx);
}

t_map	define_map(t_map map)
{
	map.map = NULL;
	map.north_file = NULL;
	map.south_file = NULL;
	map.east_file = NULL;
	map.west_file = NULL;
	map.north_found = 0;
	map.south_found = 0;
	map.east_found = 0;
	map.west_found = 0;
	map.north = -1;
	map.east = -1;
	map.south = -1;
	map.west = -1;
	map.error = 0;
	map.floor[0] = -1;
	map.floor[1] = -1;
	map.floor[2] = -1;
	map.celing[0] = -1;
	map.celing[1] = -1;
	map.celing[2] = -1;
	map.celing_found = 0;
	map.floor_found = 0;
	map.floor_color = 0;
	map.celing_color = 0;
	return (map);
}

void	death_map(t_map *map)
{
	if (!map || map->error >= 1)
		end_of_prog(*map, "Error\nFail to create a map\n");
	if (map->east <= 0 || map->south <= 0 || map->north <= 0 || map->west <= 0)
		end_of_prog(*map, "Error\nCan't open file in map\n");
	if ((map->floor[0] < 0 || map->floor[1] < 0 || map->floor[2] < 0)
		|| (map->celing[0] < 0 || map->celing[1] < 0 || map->celing[2] < 0))
		end_of_prog(*map, "Error\nCan't find RGB\n");
	map->celing_color = (255 << 24) | (map->celing[0] << 16) | \
		(map->celing[1] << 8) | map->celing[2];
	map->floor_color = (255 << 24) | (map->floor[0] << 16) | \
		(map->floor[1] << 8) | map->floor[2];
}
