/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:07:50 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/21 15:14:14 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || BUFFER_SIZE > 1000000)
		return (NULL);
	bytes_read = read_file_update_remainder(fd, &remainder[fd]);
	if (bytes_read < 0 || !remainder[fd] || *remainder[fd] == '\0')
		return (clear_remainder(&remainder[fd]));
	line = extract_line(remainder[fd]);
	remainder[fd] = save_remainder(remainder[fd]);
	return (line);
}
