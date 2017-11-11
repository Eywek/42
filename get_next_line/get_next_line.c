/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:11:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/11 16:48:06 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	*cache[2147483647];
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	ssize_t		bytes;

	if ((!cache[fd] && !(cache[fd] = ft_strnew(1))) || !line)
		return (-1);
	while (!ft_strchr(cache[fd], '\n') && (bytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
		tmp = cache[fd];
		cache[fd] = ft_strjoin(cache[fd], buffer);
		ft_strdel(&tmp);
	}
	if (bytes == -1)
		return (-1);
	if (*line && **line)
		ft_strdel(line);
	if (!*(tmp = cache[fd]))
		return (0);
	if (ft_strchr(cache[fd], '\n') > 0 && (*line = ft_strsub(cache[fd], 0, ft_strchr(cache[fd], '\n') - cache[fd])))
		cache[fd] = ft_strsub(cache[fd], (unsigned int)(ft_strlen(*line) + 1), (size_t)ft_strlen(cache[fd]));
	else
		*line = ft_strdup(cache[fd]);
	if (tmp && *tmp)
		ft_strdel(&tmp);
	return (ft_strlen(*line) > 0);
}
