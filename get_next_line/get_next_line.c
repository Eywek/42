/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:55:36 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/08 14:59:23 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "get_next_line.h"

static void		reduce_buffer(char *buffer, size_t start, size_t stop)
{
	size_t	i;

	i = 0;
	while (i < stop)
	{
		if (i < start)
			buffer[i] = buffer[start + i];
		else
			buffer[i] = 0;
		++i;
	}
}

static size_t	ft_sfind(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

static size_t	concat(char *buffer, char **line, size_t size)
{
	size_t		pos;

	if ((pos = ft_sfind(buffer, '\n')))
	{
		//if (*line)
		//	*line = ft_strjoin(*line, "\n");
		*line = ft_strjoin(*line, ft_strsub(buffer, 0, pos));
		reduce_buffer(buffer, pos + 1, (size_t)size);
		return (pos);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	ssize_t		bytes;
	ssize_t		bytes_count;
	int			size;
	size_t		pos;
	static char	buffer[BUFF_SIZE];

	if (line != NULL)
		ft_strdel(line);
	*line = ft_strnew(1);
	bytes = 0;
	bytes_count = 0;
	if ((size = ft_strlen(buffer)) > 0)
	{
		if ((pos = concat(buffer, line, (size_t)size)))
			bytes_count = (size_t)size - pos + 1;
	}
	else
		while ((bytes = read(fd, buffer, BUFF_SIZE)) > 0)
		{
			concat(buffer, line, (size_t)bytes);
			bytes_count += bytes;
		}
	if (bytes_count > 0)
		return (1);
	return (bytes);
}
