/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nfree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:59:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/17 09:45:35 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	nfree(void **target)
{
	void	*tmp;

	if (target && *target)
		free(*target);
	tmp = NULL;
	*target = tmp;
}
