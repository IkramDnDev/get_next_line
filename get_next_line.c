/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:56:58 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/21 15:15:38 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clear_remainder(char **remainder)
{
	free(*remainder);
	*remainder = NULL;
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
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 1000000)
		return (NULL);
	bytes_read = read_file_update_remainder(fd, &remainder);
	if (bytes_read < 0 || !remainder || *remainder == '\0')
		return (clear_remainder(&remainder));
	line = extract_line(remainder);
	remainder = save_remainder(remainder);
	return (line);
}
