/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nfree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:59:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/07/12 12:19:11 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"


#include <stdio.h>

void	nfree(void **target)
{
	void	*tmp;

	free(*target);
	tmp = NULL;
	*target = tmp;
}