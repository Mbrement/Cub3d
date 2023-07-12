/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   add_tab.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ngennaro <ngennaro@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/07/11 14:00:52 by ngennaro		  #+#	#+#			 */
/*   Updated: 2023/07/11 14:27:58 by ngennaro		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

char	**add_tab(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = malloc(sizeof(char *) * (ft_tablen(tab) + 2));
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	new_tab[i + 1] = NULL;
	free(str);
	free_tab(tab);
	return (new_tab);
}
