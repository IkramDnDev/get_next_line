/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:07:50 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/22 16:13:39 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*save_remainder(char *remainder)
{
	int		i;
	int		j;
	char	*new_remainder;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = malloc(ft_strlen(remainder) - i);
	if (!new_remainder)
	{
		free(remainder);
		return (NULL);
	}
	i++;
	j = 0;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	free(remainder);
	return (new_remainder);
}

char	*clear_remainder(char **remainder)
{
	if (*remainder)
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (NULL);
}

int	read_file_update_remainder(int fd, char **remainder)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = *remainder;
		*remainder = ft_strjoin(*remainder, buffer);
		free(temp);
		if (!*remainder)
			return (-1);
		if (ft_strchr(*remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	static char	*remainder[MAX_FD];
	char		*line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_file_update_remainder(fd, &remainder[fd]);
	if (bytes_read < 0 || !remainder[fd] || *remainder[fd] == '\0')
		return (clear_remainder(&remainder[fd]));
	line = extract_line(remainder[fd]);
	remainder[fd] = save_remainder(remainder[fd]);
	return (line);
}
