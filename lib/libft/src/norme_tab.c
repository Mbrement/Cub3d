/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:47:32 by ngennaro          #+#    #+#             */
/*   Updated: 2023/07/11 14:49:18 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>

char	*ft_strnew(int size)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**norme_tab(char **tab)
{
	size_t	i;
	size_t	max;

	i = 0;
	max = 0;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > max)
			max = ft_strlen(tab[i]);
		i++;
	}
	i = 0;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) < max)
		{
			tab[i] = ft_strjoin_free(tab[i],
					ft_strnew(max - ft_strlen(tab[i])));
			if (!tab[i])
				return (NULL);
		}
		i++;
	}
	return (tab);
}

