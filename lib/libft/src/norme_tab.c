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

char	*join_free(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (free(s1), NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
	while (s1[i] || s1[i] == '\n')
	{
		str[i] = s1[i];
		i ++;
	}
	i--;
	while (s2[j++])
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (free(s1), str);
}

char	**norme_tab(char **tab)
{
	size_t	i;
	size_t	max;
	char	*str_new;

	i = 0;
	max = 0;
	while (tab[i++])
	{
		if (ft_strlen(tab[i]) > max)
			max = ft_strlen(tab[i]);
	}
	i = 0;
	while (tab[i++])
	{
		str_new = ft_strnew(max - ft_strlen(tab[i]));
		if (!str_new)
			return (NULL);
		tab[i] = join_free(tab[i], str_new);
		if (!tab[i])
			return (NULL);
		nfree((void **)&str_new);
	}
	return (tab);
}

