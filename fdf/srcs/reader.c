/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:17:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 19:58:14 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf.h"

t_list	*ft_move_points(t_list *points, t_options options, t_point move,
						  int old_zoom)
{
	t_list	*ptr;
	t_point	*point;

	ptr = points;
	while (ptr)
	{
		point = ptr->content;
		if (move.x > 0 || move.y > 0 || old_zoom > 1)
			point->h /= options.amplifier;
		point->x = ((point->x / old_zoom) + move.x) * options.zoom;
		point->y = (((point->y + point->h) / old_zoom) + move.y) * options.zoom - point->h;
		point->h *= options.amplifier;
		ptr = ptr->next;
	}
	return (points);
}

t_point	*ft_new_point(int x, int y, int h, int index)
{
	t_point	*point;

	if (!(point = malloc(sizeof(t_point))))
		ft_throw_error();
	point->x = x;
	point->y = y - h;
	point->h = h;
	point->index = index;
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
		if (!(tmp = ft_lstnew(ft_new_point(x - y, y + x, ft_atoi(*tab), y),
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
	t_point	move;
	char	*line;
	int		y;

	points = NULL;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_generate_points_from_line(&points, line, y, options);
		++y;
	}
	move.x = 0;
	move.y = 0;
	ft_move_points(points, options, move, 1);
	return (points);
}
