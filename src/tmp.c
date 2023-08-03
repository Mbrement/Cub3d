/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:07:43 by mbrement          #+#    #+#             */
/*   Updated: 2023/08/03 19:44:43 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


#define BUFFER_SIZE 1

size_t	len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

char	*join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (free((void *)s1), NULL);
	str = malloc(sizeof(char) * (len(s1) + len(s2) + 1));
	if (!str)
		return (free((void *)s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free ((void *)s1);
	return (str);
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
	line = join(line, parsed_buffer);
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
		line = join(line, buffer);
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
