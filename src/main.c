/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:33:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/14 14:57:50 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	if (argc != 2)
		return ((void)printf("Wrong number of argument\n"), 1);
	check_file(argv[1]);
}
