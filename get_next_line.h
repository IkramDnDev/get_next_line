/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:57:06 by idahhan           #+#    #+#             */
/*   Updated: 2024/11/22 16:11:58 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *s, int c);
char	*extract_line(char *buff);
char	*save_remainder(char *remainder);
char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *s);
#endif
