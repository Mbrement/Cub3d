/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:33:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/12 10:59:19 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	death_map(t_map *map);

void	end_of_prog(t_map map)
{
	if (map.north_found && map.north > 2)
		close(map.north);
	if (map.east_found && map.east > 2)
		close(map.east);
	if (map.south_found && map.south > 0)
		close(map.south);
	if (map.west_found && map.west > 2)
		close(map.west);
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	t_map map;

	if (argc != 2)
		return ((void)printf("Wrong number of argument\n"), 1);
	map = check_file(argv[1]);
	death_map(&map);
	//debug
	printf("floor : %i|%i|%i|%i\nceling : %i|%i|%i|%i|\n", map.floor[0], map.floor[1], map.floor[2], map.floor_color, map.celing[0], map.celing[1], map.celing[2], map.celing_color);
	printf("north %i| south %i| east %i| west%i\n", map.north, map.south, map.east, map.west);
	printf("sucess\n");
	//end of debug
	ft_mlx(map);
	end_of_prog(map);
	// free(map);
}


void	death_map(t_map *map)
{
	if (!map || map->error >= 1)
	{
		end_of_prog(*map);
		exit(printf("Fail to create a map\n"));
	}
	if (map->east <= 0 || map->south <= 0 || map->north <= 0 || map->west <= 0)
	{
		(void)printf("Can't open file in map\n");
		end_of_prog(*map);
		exit(1);
	}
	if (map->floor[0] < 0 || map->floor[1] < 0 || map->floor[2] < 0)
	{
		(void)printf("Can't find RGB\n");
		end_of_prog(*map);
		exit(1);
	}
	if (map->celing[0] < 0 || map->celing[1] < 0 || map->celing[2] < 0)
	{
		(void)printf("Can't find RGB\n");
		end_of_prog(*map);
		exit(1);
	}
	map->celing_color = (255 << 24) | (map->celing[0] << 16) | \
		(map->celing[1] << 8) | map->celing[2];
	map->floor_color = (255 << 24) | (map->floor[0] << 16) | \
		(map->floor[1] << 8) | map->floor[2];
}
