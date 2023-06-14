/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:52:33 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/14 14:08:35 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_map(char *map)
{
	if (open(map, R_OK) <= 0)
	{
		(void)printf("Unreadable map\n");
		exit(1);
	}
	if (ft_strlen(map) < 5)
	{
		(void)printf("Incorrect format of map\n");
		exit(1);
	}
	if (ft_strcmp(map+ft_strlen(map) - 5, ".cub") != 0)
	{
		(void)printf("Incorrect format of map\n");
		exit(1);
	}
}
