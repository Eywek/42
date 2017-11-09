/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:54:13 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/09 14:37:10 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "get_next_line.h"

static t_cache	*find_fd_from_cache(t_cache *cache, const int fd)
{
	t_cache	*ptr;

	ptr = cache;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void			create_cache_line(t_cache **cache, const int fd, char *tmp)
{
	t_cache	*ptr;
	t_cache	*list;
	int		pos;

	if (!(list = (t_cache*)ft_memalloc(sizeof(t_cache))))
		return ;
	if (ft_strchr(tmp, '\n') || (pos = ft_strlen(tmp) < BUFF_SIZE))
		list->content = ft_strsub(tmp, (pos) ? pos : ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp));
	else 
		list->content = ft_strdup(tmp);
	list->fd = fd;
	list->next = NULL;
	if (*cache)
	{
		ptr = *cache;
		while (ptr && ptr->fd != fd)
			ptr = ptr->next;
		*ptr = *list;
	}
	else
		*cache = list;
}

int				get_next_line(const int fd, char **line)
{
	static t_cache	*cache;
	char			buffer[BUFF_SIZE];
	char			*tmp;
	ssize_t			bytes;
	ssize_t			bytes_count;

	bytes = 0;
	bytes_count = 0;
	while ((bytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		tmp = ft_strjoin(ft_strnew(1), buffer);
		bytes_count += bytes;
	}
	if (bytes_count <= 0)
	{
		if (find_fd_from_cache(cache, fd) == NULL)
			return (-1);
		tmp = find_fd_from_cache(cache, fd)->content;
	}
	ft_strdel(line);
	if (ft_strchr(tmp, '\n') || ft_strlen(tmp) < BUFF_SIZE)
		*line = ft_strsub(tmp, 0, (ft_strlen(tmp) < BUFF_SIZE) ? ft_strlen(tmp) : ft_strchr(tmp, '\n') - tmp);
	else
		*line = ft_strdup(tmp);
	create_cache_line(&cache, fd, tmp);
	if (ft_strlen(*line) > 0)
		return (1);
	else
		return (bytes);
}
