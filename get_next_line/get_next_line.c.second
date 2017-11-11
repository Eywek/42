/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:55:36 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/08 18:29:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "get_next_line.h"

static void		ft_reduce_buffer(char *buffer, size_t start, size_t stop)
{
	char	tmp[BUFF_SIZE];
	size_t	i;
	size_t	index;

	//printf("reduce buffer from %zu to %zu\n", start, stop);
	i = -1;
	index = 0;
	while (++i < stop)
		if (i >= start)
		{
			tmp[index] = buffer[start + index];
			++index;
		}
	i = -1;
	while (++i < stop)
		buffer[i] = 0;
	i = 0;
	while (start++ < stop)
	{
		buffer[i] = tmp[i];
		++i;
	}
	//printf("reduced buffer : '%s'\n", buffer);
}

static size_t	ft_sfind(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		//printf("str[%zu] = %c\n", i, str[i]);
		if (str[i] == c)
			return (i);
		++i;
	}
	return (0);
}

static size_t	ft_concat(char *buffer, char **line, size_t size)
{
	size_t		pos;

	if ((pos = ft_sfind(buffer, '\n')) > 0 ||
			(pos = ft_strlen(buffer)) != BUFF_SIZE)
	{
		*line = ft_strjoin(*line, ft_strsub(buffer, 0, pos));
		ft_reduce_buffer(buffer, pos + 1, (size_t)size);
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

	//printf("last buffer = '%s' (%d chars)\n", buffer, ft_strlen(buffer));
	//if (line != NULL)
	//	ft_strdel(line);
	*line = ft_strnew(1);
	bytes = 0;
	bytes_count = 0;
	if ((size = ft_strlen(buffer)) > 0)
	{
		if ((pos = ft_concat(buffer, line, (size_t)size)))
			bytes_count = (size_t)size - pos + 1;
	}
	else
		while ((bytes = read(fd, buffer, BUFF_SIZE)) > 0)
		{
			//printf("buffer = '%s'\n", buffer);
			if (ft_concat(buffer, line, (size_t)bytes) > 0)
				break ;
			bytes_count += bytes;
		}
	if (bytes_count > 0)
		return (1);
	return (bytes);
}
