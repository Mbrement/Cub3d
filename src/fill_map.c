/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:29:17 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/13 13:58:11 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	void	is_wall(t_map *map, int i_am, char *str)
{
	if (i_am == 1 && map->north <= 0)
	{
		map->north_file = ft_strdup(str);
		if (map->north_file)
			map->north = open(map->north_file, R_OK);
	}
	else if (i_am == 2 && map->south <= 0)
	{
		map->south_file = ft_strdup(str);
		if (map->south_file)
			map->south = open(map->south_file, R_OK);
	}
	else if (i_am == 3 && map->west <= 0)
	{
		map->west_file = ft_strdup(str);
		if (map->west_file)
			map->west = open(map->west_file, R_OK);
	}
	else if (i_am == 4 && map->east <= 0)
	{
		map->east_file = ft_strdup(str);
		if (map->east_file)
			map->east = open(map->east_file, R_OK);
	}
}

void	fill_map_err( char *buffer, t_map *map, char	*str, char	*tmp)
{
	nfree((void **)&buffer);
	nfree((void **)&str);
	nfree((void **)&tmp);
	end_of_prog(*map, "Error\nWrong format file\n");
}

void	fill_i_am(int i_am, char *buffer, t_map *map, char	*str)
{
	if (i_am == 5 || i_am == 6)
		rgb(buffer + 1, map, i_am - 4);
	else if (ft_strlen(str) < 4 || ft_strcmp(str + \
			ft_strlen(str) - 4, ".xpm") != 0)
		map->error = 1;
	else if (i_am >= 1 && i_am <= 4 && (map->north <= 0 || \
		map->south <= 0 || map->west <= 0 || map->east <= 0))
		is_wall(map, i_am, str);
	else
		map->error = 1;
}

int	fill_map_start(char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i] == ' ')
		;
	i += 2;
	while (buffer[++i] == ' ')
		;
	return (i);
}

void	fill_map(int i_am, char *buffer, t_map *map, int file_fd)
{
	int		i;
	char	*str;
	char	*tmp;

	i = fill_map_start(buffer);
	str = ft_strdup(buffer + i);
	if (!str)
	{
		nfree((void **)&buffer);
		end_of_prog(*map, "Error\nMalloc error\n");
	}
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	tmp = ft_strjoin("./", str);
	if (!tmp)
		fill_map_err(buffer, map, str, tmp);
	fill_i_am(i_am, buffer, map, str);
	if (map->error == 1 || (!map->north || !map->south || \
		!map->west || !map->east))
	{
		close(file_fd);
		fill_map_err(buffer, map, str, tmp);
	}
	nfree((void **)&str);
	nfree((void **)&tmp);
}
