/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:52:33 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/14 16:26:47 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>

static void		check_format(char *map, int file_fd);
static t_map	*check_inside(int file_fd);

void	check_file(char *map)
{
	int		file_fd;
	t_map	*true_map;

	file_fd = open(map, R_OK);
	check_format(map, file_fd);
	true_map = check_inside(file_fd);
}

static void	check_format(char *map, int file_fd)
{
	if (file_fd <= 0)
	{
		(void)printf("Unreadable map\n");
		close(file_fd);
		exit(1);
	}
	if (ft_strlen(map) < 5)
	{
		(void)printf("Incorrect format of map\n");
		close(file_fd);
		exit(1);
	}
	if (ft_strcmp(map + ft_strlen(map) - 4, ".cub") != 0)
	{
		(void)printf("Incorrect format of map\n");
		close(file_fd);
		exit(1);
	}
}

static int	what_is_it(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	write(1, "hi\n", 3);
	while (str && str[i])
	{
		if (str[i] == ' ')
			;
		else if (str[i] == 'N' && str[i + 1] && str[i + 1] == 'O')
		{
			result = 1;
			break ;
		}
		else if (str[i] == 'S' && str[i + 1] && str[i + 1] == 'O')
		{
			result = 2;
			break ;
		}
		else if (str[i] == 'W' && str[i + 1] && str[i + 1] == 'E')
		{
			result = 3;
			break ;
		}
		else if (str[i] == 'E' && str[i + 1] && str[i + 1] == 'A')
		{
			result = 4;
			break ;
		}
		else if (str[i] == 'C')
		{
			result = 5;
			break ;
		}
		else if (str[i] == 'F')
		{
			result = 6;
			break ;
		}
		else
		{
			result = -1;
			break ;
		}
		i++;
	}
	return (result);
}
int	ft_atoi_rgb(char *str, int i)
{
	char	tmp[4];
	int		rtn;

	if (str[i + 1 == ','])
	{
		tmp[0] = '0';
		tmp[1] = '0';
		tmp[2] = str[i];
	}
	if (str[i + 2 == ','])
	{
		tmp[0] = '0';
		tmp[1] = str[i];
		tmp[2] = str[i + 1];
	}
	if (str[i + 3 == ','])
	{
		tmp[0] = str[i];
		tmp[1] = str[i + 1];
		tmp[2] = str[i + 2];
	}
	tmp[3] = '\0';
	rtn = ft_atoi(tmp);
	if (rtn > 255)
		rtn = -1;
	return (rtn);
}


void	rgb(char *str, t_map *map, int index)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 1;
	while (str[i] && j < 3)
	{
		while(str[i] == ' ' || str[i] == ',')
			i++;
		if (ft_isdigit(str[i]))
			tmp = ft_atoi_rgb(str, i);
		if (index == 1)
			map->celing[j] = tmp;
		if (index == 1)
			map->floor[j] = tmp;
		j++;
	}
	while(str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] != ' ')
		map->floor[0] = -1;
}

static void	fill_map(int i_am, char *buffer, t_map *map)
{
	int		i;
	char	*str;

	i = -1;
	while (buffer[++i] == ' ')
		;
	i += 2;
	while (buffer[++i] == ' ')
		;
	str = ft_strdup(buffer + i);
	if (i_am == 1)
		map->north = open(str, R_OK);
	else if (i_am == 2)
		map->south = open(str, R_OK);
	else if (i_am == 3)
		map->west = open(str, R_OK);
	else if (i_am == 4)
		map->east = open(str, R_OK);
	else if (i_am == 5)
		rgb(str, map, 1);
	else if (i_am == 6)
		rgb(str, map, 2);
	free(str);
	free(buffer);
}

static t_map	*check_inside(int file_fd)
{
	char	*buffer;
	t_map	*map;
	int		i_am;

	map = malloc(sizeof(t_map));
	while (1)
	{
		buffer = get_next_line(file_fd);
		if (!buffer || buffer[0] == '\0')
			break ;
		i_am = what_is_it(buffer);
		if (i_am < 0)
		{
			(void)printf("Incorrect line in the map\n");
			while(buffer)
			{	
				free(buffer);
				buffer = get_next_line(file_fd);
			}
			close(file_fd);
			exit(1);
		}
		else if (i_am > 0)
			fill_map(i_am, buffer, map);
	}
	return (map);
}
