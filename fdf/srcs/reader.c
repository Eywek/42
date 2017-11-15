/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:17:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/15 14:55:49 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf.h"

t_point	*ft_new_point(int x, int y, int h)
{
	t_point	*point;

	if (!(point = malloc(sizeof(t_point))))
		ft_throw_error();
	point->x = x * 10;
	point->y = y * 10 - h;
	point->h = h;
	point->index = y;
	return (point);
}

int 	ft_open_file(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

t_list	*ft_read(int fd)
{
	t_list	*points;
	char	*line;
	t_list	*tmp;
	int 	x;
	int 	y;
	char 	**tab;

	points = NULL;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		tab = ft_strsplit(line, ' ');
		while (*tab)
		{
			if (!(tmp = ft_lstnew(ft_new_point(x, y, ft_atoi(*tab)), sizeof(t_point))))
				ft_throw_error();
			if (points)
				ft_lstaddend(&points, tmp);
			else
				ft_lstadd(&points, tmp);
			++tab;
			++x;
		}
		++y;
	}
	return (points);
}
