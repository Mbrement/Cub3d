/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:52:33 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/10 23:28:39 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void		check_format(char *map, int file_fd);
static t_map	check_inside(int file_fd);

t_map	check_file(char *map)
{
	int		file_fd;
	t_map	true_map;

	file_fd = open(map, R_OK);
	if (file_fd <= 0)
		return ((void)printf("Coundn't open the map\n"), exit(1), true_map);
	check_format(map, file_fd);
	true_map = check_inside(file_fd);
	//debug
	close(file_fd);
	//end of debug
	return (true_map);
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

static int	what_is_it(char *str, t_map *map)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
			;
		else if (str[i] == 'N' && str[i + 1] && str[i + 1] == 'O')
		{
			result = 1;	
			map->north_found += 1;
			break ;
			if (map->north_found != 1)
			{
				printf("2 of the same parameter in map\n");
				result = -1;
			}
		}
		else if (str[i] == 'S' && str[i + 1] && str[i + 1] == 'O')
		{
			map->south_found += 1;
			result = 2;
			if (map->south_found != 1)
			{
				printf("2 of the same parameter in map\n");
				result = -1;
			}
			break ;
		}
		else if (str[i] == 'W' && str[i + 1] && str[i + 1] == 'E')
		{
			map->west_found += 1;
			result = 3;
			if (map->west_found != 1)
			{
				printf("2 of the same parameter in map\n");
				result = -1;
			}
			break ;
		}
		else if (str[i] == 'E' && str[i + 1] && str[i + 1] == 'A')
		{
			result = 4;
			map->east_found += 1;
			break ;
			if (map->east_found != 1)
			{
				printf("2 of the same parameter in map\n");
				result = -1;
			}
		}
		else if (str[i] == 'C')
		{
			map->celing_found += 1;
			result = 5;
			if (map->celing_found != 1)
			{
				printf("2 of the same parameter in map\n");
				result = -1;
			}
			break ;
		}
		else if (str[i] == 'F')
		{
			result = 6;
			map->floor_found += 1;
			break ;
			if (map->floor_found != 1)
			{
				printf("2 of the same parameter in map\n");
				result = -1;
			}
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

	if ((int)ft_strlen(str) >= i + 1 && (str[i + 1] == ',' || str[i + 1]  == ' ' || str[i + 1] == '\n'))
	{
		tmp[0] = '0';
		tmp[1] = '0';
		tmp[2] = str[i];
	}
	else if ((int)ft_strlen(str) >= i + 2 && (str[i + 2] == ',' || str[i + 2]  == ' ' || str[i + 2] == '\n'))
	{
		tmp[0] = '0';
		tmp[1] = str[i];
		tmp[2] = str[i + 1];
	}
	else if ((int)ft_strlen(str) >= i + 3 && (str[i + 3]  == ',' || str[i + 3]  == ' ' || str[i + 3] == '\n'))
	{
		tmp[0] = str[i];
		tmp[1] = str[i + 1];
		tmp[2] = str[i + 2];
	}
	else
	{
		tmp[0] = '-';
		tmp[1] = '1';
		tmp[2] = '0';
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
	j = -1;
	while (str[i] && j < 3)
	{
		tmp = -1;
		while (str[i] && (str[i] == ' ' || str[i] == ',' || str[i] == '0'))
			i++;
		if (ft_isdigit(str[i]))
		{
			tmp = ft_atoi_rgb(str, i);
			j++;
			while (ft_isdigit(str[i]))
				i++;
		}
		else
			break ;
		if (index == 1)
			map->celing[j] = tmp;
		else if (index == 2)
			map->floor[j] = tmp;
		while (str[i] && (str[i] != ' ' && str[i] != ','))
			i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
	{
		//debug
		printf("trigger by : %c at %i of %zu\n", str[i], i, ft_strlen(str) - 1);
		//end of debug
		map->floor[0] = -1;
	}
}

static void	fill_map(int i_am, char *buffer, t_map *map)
{
	int		i;
	char	*str;
	char	*tmp;

	i = -1;
	while (buffer[++i] == ' ')
		;
	i += 2;
	while (buffer[++i] == ' ')
		;
	str = ft_strdup(buffer + i);
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	tmp = ft_strjoin("./", str);
	//debug
	// (void)printf("|%s|\n", tmp);
	if (i_am == 1 && map->north <= 0)
		map->north = open(str, R_OK);
	else if (i_am == 2  && map->south <= 0)
		map->south = open(str, R_OK);
	else if (i_am == 3 && map->west <= 0)
		map->west = open(str, R_OK);
	else if (i_am == 4 && map->east <= 0)
		map->east = open(str, R_OK);
	else if (i_am == 5)
		rgb(buffer + 1, map, 1);
	else if (i_am == 6)
		rgb(buffer + 1, map, 2);
	else
		map->error = 1;
	nfree(str);
	nfree(tmp);
}

static t_map	check_inside(int file_fd)
{
	char	*buffer;
	t_map	map;
	int		i_am;

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
	map.north_found = 0;
	map.west_found = 0;
	map.east_found = 0;
	map.south_found = 0;
	map.celing_found = 0;
	map.floor_found = 0;
	while (1)
	{
		buffer = get_next_line(file_fd);
		if (!buffer || buffer[0] == '\0')
			break ;
		i_am = what_is_it(buffer, &map);
		if (i_am < 0)
		{
			(void)printf("Incorrect line in the map\n");
			while (buffer)
			{	
				nfree(buffer);
				buffer = get_next_line(file_fd);
			}
			(void)close(file_fd);
			end_of_prog(map);
			exit(1);
		}
		else if (i_am > 0)
			fill_map(i_am, buffer, &map);
		nfree(buffer);
		if (map.celing_color &&map.east &&map.west &&map.south &&map.north &&map.floor_color)
			break;
	}
	while(1)
	{
		buffer = get_next_line(file_fd);
		if (!buffer)
		{
			(void)printf("No map in map file\n");
			end_of_prog(map);
			exit(1);
		}
		else if (buffer[0] && buffer[0] != '\n')
		{
			(void)printf("Incorrect line in the map\n");
			end_of_prog(map);
			exit(1);
		}
		nfree(buffer);
	}
	//
	// parsing de la map here
	//
	nfree(buffer);
	return (map);
}
