/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:41:26 by ngennaro          #+#    #+#             */
/*   Updated: 2023/08/19 17:22:54 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	locate_player_x(char **maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps[i])
	{
		j = 0;
		while (maps[i][j])
		{
			if (maps[i][j] == 'N' || maps[i][j] == 'S' || maps[i][j] == 'E'
				|| maps[i][j] == 'W')
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

int	locate_player_y(char **maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps[i])
	{
		j = 0;
		while (maps[i][j])
		{
			if (maps[i][j] == 'N' || maps[i][j] == 'S' || maps[i][j] == 'E'
				|| maps[i][j] == 'W')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
