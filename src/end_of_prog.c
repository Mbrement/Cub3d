/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:38:25 by mbrement          #+#    #+#             */
/*   Updated: 2023/08/03 21:41:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	nfree((void **)&map.north_file);
	nfree((void **)&map.south_file);
	nfree((void **)&map.east_file);
	nfree((void **)&map.west_file);
	free_tab(map.map);
	exit(1);
}
