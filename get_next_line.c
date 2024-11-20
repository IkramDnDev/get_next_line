/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:56:58 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/20 19:20:12 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_remainder(char **remainder)
{
	free(*remainder);
	*remainder = NULL;
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
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 1000000)
		return (NULL);
	bytes_read = read_file_update_remainder(fd, &remainder);
	if (bytes_read < 0)
	{
		clear_remainder(&remainder);
		return (NULL);
	}
	if (!remainder || *remainder == '\0')
	{
		clear_remainder(&remainder);
		return (NULL);
	}
	line = extract_line(remainder);
	remainder = save_remainder(remainder);
	return (line);
}
