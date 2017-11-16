/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:17:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 16:46:38 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf.h"

t_point	*ft_new_point(int x, int y, int h, t_options options)
{
	t_point	*point;

	h *= options.amplifier;
	if (!(point = malloc(sizeof(t_point))))
		ft_throw_error();
	point->x = x * options.zoom;
	point->y = y * options.zoom - h;
	point->h = h;
	point->index = y;
	return (point);
}

int		ft_open_file(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

void	ft_generate_points_from_line(t_list **points, char *line, int y,
									t_options options)
{
	int		x;
	char	**rm;
	t_list	*tmp;
	char	**tab;

	x = 0;
	tab = ft_strsplit(line, ' ');
	rm = tab;
	while (*tab)
	{
		if (!(tmp = ft_lstnew(ft_new_point(x, y, ft_atoi(*tab), options),
							sizeof(t_point))))
			ft_throw_error();
		if (*points)
			ft_lstaddend(points, tmp);
		else
			ft_lstadd(points, tmp);
		free(*tab);
		++tab;
		++x;
	}
	free(rm);
}

t_list	*ft_read(int fd, t_options options)
{
	t_list	*points;
	char	*line;
	int		y;

	points = NULL;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_generate_points_from_line(&points, line, y, options);
		++y;
	}
	return (points);
}
