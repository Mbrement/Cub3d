/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:13:39 by mbrement          #+#    #+#             */
/*   Updated: 2023/08/04 01:12:36 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_tab(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (&str[i])
			nfree((void **)&str[i]);
		i++;
	}
	nfree((void **)&str);
}

void	free_tab_size_t(size_t *target)
{
	size_t	i;

	i = 0;
	if (!target)
		return ;
	while (target[i])
	{
		if (target[i])
			nfree((void **)&target[i]);
		i++;
	}
	nfree((void **)&target);
}
