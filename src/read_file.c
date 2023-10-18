/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:49:54 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/13 11:04:30 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include <unistd.h>

void	read_params(char **buffer, t_map *map, int file_fd)
{
	int	i_am;
	int	count;

	count = 0;
	while (1)
	{
		*buffer = get_next_line(file_fd);
		if (!*buffer || (*buffer)[0] == '\0')
			break ;
		i_am = what_is_it(*buffer, map);
		if (i_am < 0)
		{
			free(*buffer);
			(void)close(file_fd);
			end_of_prog(*map, "Error\nIncorrect line in the map\n");
		}
		else if (i_am > 0)
		{
			count++;
			fill_map(i_am, *buffer, map, file_fd);
		}
		nfree((void **)buffer);
		if (count >= 6)
			break ;
	}
}

char	**create_map(int file_fd, t_map map, char *buffer)
{
	char	**maps;

	maps = malloc(sizeof(char *) * 2);
	if (!maps)
	{
		nfree((void **)&buffer);
		close(file_fd);
		end_of_prog(map, "Error\nMalloc error\n");
	}
	maps[0] = NULL;
	maps[1] = NULL;
	maps = add_tab(maps, buffer);
	if (!maps)
	{
		nfree((void **)&buffer);
		end_of_prog(map, "Error\nMalloc error\n");
	}
	return (maps);
}

char	**line_on_map(char **maps, int file_fd, t_map map, char *buffer)
{
	while (1)
	{
		buffer = get_next_line(file_fd);
		if (!buffer)
			break ;
		if (buffer[0] == '\n')
		{
			close(file_fd);
			free(buffer);
			free_tab(maps);
			end_of_prog(map, "Error\nEmpty line in map\n");
		}
		maps = add_tab(maps, buffer);
		if (!maps)
		{
			close(file_fd);
			end_of_prog(map, "Error\nMalloc error\n");
		}
	}
	maps = add_tab(maps, ft_strnew(1));
	if (!maps)
		end_of_prog(map, "Error\nMalloc error\n");
	return (maps);
}

t_map	check_inside(int file_fd, t_map map)
{
	char	**maps;
	char	*buffer;

	read_params(&buffer, &map, file_fd);
	while (1)
	{
		buffer = get_next_line(file_fd);
		if (!buffer)
		{
			close(file_fd);
			end_of_prog(map, "Error\nNo map in map file\n");
		}
		else if (buffer[0] && buffer[0] != '\n')
			break ;
		nfree((void **)&buffer);
	}
	maps = create_map(file_fd, map, buffer);
	maps = line_on_map(maps, file_fd, map, buffer);
	(void)close(file_fd);
	map.map = maps;
	if (!check_chr_map(maps))
		end_of_prog(map, "Error\nIncorrect map\n");
	if (!check_walls(&map))
		end_of_prog(map, "Error\nIncorrect map\n");
	return (map);
}
