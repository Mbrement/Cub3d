/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:55:43 by ngennaro          #+#    #+#             */
/*   Updated: 2023/07/13 14:58:43 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_chr_map(char **maps)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (maps[i])
	{
		j = 0;
		while (maps[i][j])
		{
			if (maps[i][j] != '1' && maps[i][j] != '0' && maps[i][j] != '\n'
				&& maps[i][j] != 'N' && maps[i][j] != 'S' && maps[i][j] != 'E'
				&& maps[i][j] != 'W' && maps[i][j] != ' ')
				return (0);
			if (maps[i][j] == 'N' || maps[i][j] == 'S' || maps[i][j] == 'E'
				|| maps[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (0);
	return (1);
}

char	**dup_maps(char **maps)
{
	int		i;
	char	**dup;

	i = 0;
	while (maps[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (maps[i])
	{
		dup[i] = ft_strdup(maps[i]);
		if (!dup[i])
			return (free_tab(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	replace_chr(char **temp_maps, int x, int y, int *new)
{
	if (temp_maps[x + 1][y] == '0')
	{
		*new = 1;
		temp_maps[x + 1][y] = '*';
	}
	if (temp_maps[x - 1][y] == '0')
	{
		*new = 1;
		temp_maps[x - 1][y] = '*';
	}
	if (temp_maps[x][y + 1] == '0')
	{
		*new = 1;
		temp_maps[x][y + 1] = '*';
	}
	if (temp_maps[x][y - 1] == '0')
	{
		*new = 1;
		temp_maps[x][y - 1] = '*';
	}
}

int	death_around(char **temp_maps, int x, int y)
{
	if (temp_maps[x + 1][y] != '1' && temp_maps[x + 1][y] != '0'
		&& temp_maps[x + 1][y] != '*')
		return (1);
	if (temp_maps[x - 1][y] != '1' && temp_maps[x - 1][y] != '0'
		&& temp_maps[x - 1][y] != '*')
		return (1);
	if (temp_maps[x][y + 1] != '1' && temp_maps[x][y + 1] != '0'
		&& temp_maps[x][y + 1] != '*')
		return (1);
	if (temp_maps[x][y - 1] != '1' && temp_maps[x][y - 1] != '0'
		&& temp_maps[x][y - 1] != '*')
		return (1);
	return (0);
}

int	complete_map(char **temp_maps)
{
	int		x;
	int		y;
	int		new;

	new = 1;
	while (new != 0)
	{
		x = 0;
		new = 0;
		while (temp_maps[x] && temp_maps[x][0] != '\n')
		{
			y = 0;
			while (temp_maps[x][y])
			{
				if (temp_maps[x][y] == '*')
				{
					if (death_around(temp_maps, x, y))
						return (0);
					replace_chr(temp_maps, x, y, &new);
				}
				y++;
			}
			x++;
		}
	}
	return (1);
}

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
