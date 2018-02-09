/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:11:41 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/09 17:07:31 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static int	ft_free_gnl(char *tmp)
{
	ft_strdel(&tmp);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*c[127];
	char		buffer[BUFF_SIZE_GNL + 1];
	char		*tmp;
	ssize_t		b;
	int			endl;

	if (fd < 0 || (!c[fd] && !(c[fd] = ft_strnew(1))) || !line)
		return (-1);
	while (!ft_strchr(c[fd], '\n') && (b = read(fd, buffer, BUFF_SIZE_GNL)) > 0)
	{
		buffer[b] = '\0';
		tmp = c[fd];
		c[fd] = ft_strjoin(c[fd], buffer);
		ft_strdel(&tmp);
	}
	if ((b == -1 || !*(tmp = c[fd])) && ft_free_gnl(tmp))
		return (b == -1 ? -1 : 0);
	if ((endl = (ft_strchr(c[fd], '\n') > 0)))
		*line = ft_strsub(c[fd], 0, ft_strchr(c[fd], '\n') - c[fd]);
	else
		*line = ft_strdup(c[fd]);
	c[fd] = ft_strsub(c[fd], (unsigned int)(ft_strlen(*line) + endl),
			(size_t)(ft_strlen(c[fd]) - (ft_strlen(*line) + endl)));
	ft_strdel(&tmp);
	return (!(!c[fd] && !ft_strlen(*line)));
}
