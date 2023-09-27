/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:13:39 by mbrement          #+#    #+#             */
/*   Updated: 2023/09/27 04:45:35 by kali             ###   ########lyon.fr   */
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
