/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:54:13 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/09 14:41:50 by vtouffet         ###   ########.fr       */
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

void			create_cache_line(t_cache **cache, const int fd, char *tmp, int size)
{
	t_cache	*ptr;
	t_cache	*list;

	if (!(list = (t_cache*)ft_memalloc(sizeof(t_cache))))
		return ;
	list->content = ft_strsub(tmp, (unsigned int)size + 1, (size_t)(ft_strlen(tmp) - size));
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

int                get_next_line(const int fd, char **line)
{
    static t_cache  *cache;
    char            buffer[BUFF_SIZE + 1];
    ssize_t         bytes;
    char 			*tmp;
    char            *remove;

    if (find_fd_from_cache(cache, fd))
        tmp = find_fd_from_cache(cache, fd)->content;
    else
        tmp = ft_strnew(1);
    while (ft_strchr(tmp, '\n') == NULL && (bytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
        remove = tmp;
		tmp = ft_strjoin(tmp, buffer);
        ft_strdel(&remove);
	}
	if (bytes == -1 || !line)
		return (-1);
    /*ft_putstr(tmp);
    ft_putchar('\n');
    ft_putnbr(ft_strlen(tmp)); // 16
    ft_putchar('\n');
    ft_strsub(tmp, 0, 2);
    ft_putchar('\n');
    ft_putnbr(ft_strlen(tmp)); // 18*/

    if (ft_strchr(tmp, '\n'))
		*line = ft_strsub(tmp, 0, ft_strchr(tmp, '\n') - tmp);
	else
		*line = ft_strdup(tmp);
    create_cache_line(&cache, fd, tmp, ft_strlen(*line));
    return (ft_strlen(tmp) > 0);
}

int                get_next_line_t(const int fd, char **line)
{
    static char     *cache[256];
    char            buffer[BUFF_SIZE + 1];
    ssize_t         bytes;
    char 			*tmp;
    char            *remove;

    if (fd >= 0 && cache[fd])
        tmp = cache[fd];
    else
        tmp = ft_strnew(1);
    while (ft_strchr(tmp, '\n') == NULL && (bytes = read(fd, buffer, BUFF_SIZE)) > 0)
    {
        buffer[bytes] = '\0';
        remove = tmp;
        tmp = ft_strjoin(tmp, buffer);
        ft_strdel(&remove);
    }
    if (bytes == -1 || !line)
        return (-1);
    if (ft_strchr(tmp, '\n'))
        *line = ft_strsub(tmp, 0, ft_strchr(tmp, '\n') - tmp);
    else
        *line = ft_strdup(tmp);
    cache[fd] = ft_strsub(tmp, (unsigned int)ft_strlen(*line) + 1, (size_t)(ft_strlen(tmp) - ft_strlen(*line)));
    return (ft_strlen(tmp) > 0);
}
