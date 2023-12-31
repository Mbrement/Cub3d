/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:07:43 by mbrement          #+#    #+#             */
/*   Updated: 2023/10/10 10:14:58 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define BUFFER_SIZE 1

int	is_end_line(const char *str, size_t *index)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}

void	buffer_clear(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
}

char	*buffer_parse(char *buffer, size_t index)
{
	char	*next;
	size_t	i;

	i = 0;
	next = malloc(sizeof(char) * (index + 2));
	if (!next)
		return (NULL);
	while (i <= index)
	{
		next[i] = buffer[i];
		i++;
	}
	next[i] = '\0';
	i = 0;
	index ++;
	while (buffer[i + index] != '\0')
	{
		buffer[i] = buffer[i + index];
		i++;
	}
	buffer[i] = '\0';
	return (next);
}

char	*return_end_line(char *line, char *parsed_buffer)
{
	if (!parsed_buffer)
		return (free(line), NULL);
	line = ft_strjoin_free(line, parsed_buffer);
	free(parsed_buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		check;
	size_t		index;
	char		*line;

	check = 1;
	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (check != 0)
	{
		if (is_end_line(buffer, &index))
			return (return_end_line(line, buffer_parse(buffer, index)));
		line = ft_strjoin_free(line, buffer);
		if (!line)
			return (buffer_clear(buffer, BUFFER_SIZE + 1), NULL);
		check = read(fd, buffer, BUFFER_SIZE);
		buffer[check] = '\0';
		if (check == -1)
			return (free(line), buffer_clear(buffer, BUFFER_SIZE + 1), NULL);
	}
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
