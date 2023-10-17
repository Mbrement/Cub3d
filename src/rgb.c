/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:49:18 by ngennaro          #+#    #+#             */
/*   Updated: 2023/10/17 11:52:25 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	rgb_other_case(char *str, int i, char tmp[4])
{
	if ((int)ft_strlen(str) >= i + 2 && (str[i + 2]
			== ',' || str[i + 2] == ' ' || str[i + 2] == '\n'))
	{
		tmp[0] = '0';
		tmp[1] = str[i];
		tmp[2] = str[i + 1];
	}
	else if ((int)ft_strlen(str) >= i + 3 && (str[i + 3]
			== ',' || str[i + 3] == ' ' || str[i + 3] == '\n'))
	{
		tmp[0] = str[i];
		tmp[1] = str[i + 1];
		tmp[2] = str[i + 2];
	}
	else if ((str[i] == ' ' || str[i] == ','))
	{
		tmp[0] = str[i - 1];
		tmp[1] = str[i];
		tmp[2] = str[i + 1];
	}
	else
		ft_strlcpy(tmp, "-10", 3);
}

int	ft_atoi_rgb(char *str, int i)
{
	char	tmp[4];
	int		rtn;

	while (str && str[i] && str[i] == '0' && str[i + 1] && str[i + 1] != '\n')
		i++;
	if ((int)ft_strlen(str) >= i + 1 && (str[i + 1]
			== ',' || str[i + 1] == ' ' || str[i + 1] == '\n'))
	{
		tmp[0] = '0';
		tmp[1] = '0';
		tmp[2] = str[i];
	}
	else
		rgb_other_case(str, i, tmp);
	tmp[3] = '\0';
	rtn = ft_atoi(tmp);
	if (rtn > 255)
		rtn = -1;
	return (rtn);
}

int	format_rgb(char *str, int *i, int index, t_map *map)
{
	int	tmp;
	int	j;

	j = -1;
	while (str[*i] && j < 3)
	{
		tmp = -1;
		while (str[*i] && (str[*i] == ' ' || str[*i] == ','))
			*i = *i + 1;
		if (j++ < 2 && ft_isdigit(str[*i]))
		{
			tmp = ft_atoi_rgb(str, *i);
			while (ft_isdigit(str[*i]))
				*i = *i + 1;
		}
		else
			break ;
		if (index == 1)
			map->celing[j] = tmp;
		else if (index == 2)
			map->floor[j] = tmp;
		while (str[*i] && (str[*i] != ' ' && str[*i] != ','))
			*i = *i + 1;
	}
	return (j);
}

void	rgb(char *str, t_map *map, int index)
{
	int	i;

	i = 0;
	if (format_rgb(str, &i, index, map) != 2)
		map->error = 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		map->floor[0] = -1;
}
