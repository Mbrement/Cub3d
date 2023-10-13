/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:29:17 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/13 12:31:43 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	fill_map(int i_am, char *buffer, t_map *map, int file_fd)
{
	int		i;
	char	*str;
	char	*tmp;
	Bool	error;

	i = -1;
	error = 0;
	while (buffer[++i] == ' ')
		;
	i += 2;
	while (buffer[++i] == ' ')
		;
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
	{
		nfree((void **)&str);
		nfree((void **)&buffer);
		end_of_prog(*map, "Error\nMalloc error\n");
	}
	if (i_am == 5)
		rgb(buffer + 1, map, 1);
	else if (i_am == 6)
		rgb(buffer + 1, map, 2);
	else if (ft_strlen(str) < 4 || ft_strcmp(str + \
			ft_strlen(str) - 4, ".xpm") != 0)
		error = 1;
	else if (i_am == 1 && map->north <= 0)
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
	else
		map->error = 1;
	if (error == 1 || (!map->north || !map->south || !map->west \
			|| !map->east))
	{
		nfree((void **)&buffer);
		nfree((void **)&str);
		nfree((void **)&tmp);
		close(file_fd);
		end_of_prog(*map, "Error\nWrong format file\n");
	}
	nfree((void **)&str);
	nfree((void **)&tmp);
}
