/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:17:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 11:58:27 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_list	*ft_move_points(t_list *points, t_options options, t_point move,
						t_options old_options)
{
	t_list	*ptr;
	t_point	*point;

	ptr = points;
	while (ptr)
	{
		point = ptr->content;
		point->y = (point->y + point->h);
		if (move.x > 0 || move.y > 0 || old_options.zoom > 1)
			point->h /= old_options.amplifier;
		point->x = ((point->x / old_options.zoom) + move.x) * options.zoom;
		point->h *= options.amplifier;
		point->y = ((point->y / old_options.zoom) + move.y) * options.zoom
				- point->h;
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

void	ft_generate_points_from_line(t_list **points, char *line, int y)
{
	int		x;
	char	**rm;
	t_list	*tmp;
	char	**tab;
	t_point	*point;

	x = -1;
	if (!(tab = ft_strsplit(line, ' ')))
		ft_throw_error();
	rm = tab;
	while (*tab && ++x >= 0)
	{
		if (!ft_is_valid(*tab))
			ft_throw_error();
		point = ft_new_point(x - y, y + x, ft_atoi(*tab), y);
		if (!(tmp = ft_lstnew(point, sizeof(t_point))))
			ft_throw_error();
		free(point);
		if (*points)
			ft_lstaddend(points, tmp);
		else
			ft_lstadd(points, tmp);
		free(*(tab++));
	}
	free(rm);
}

t_list	*ft_read(int fd, t_options options, t_options old_options)
{
	t_list	*points;
	t_point	move;
	char	*line;
	int		y;
	int		state;

	points = NULL;
	y = 0;
	while ((state = get_next_line(fd, &line)) > 0)
	{
		ft_generate_points_from_line(&points, line, y);
		free(line);
		++y;
	}
	if (state == -1)
		ft_throw_error();
	move.x = 0;
	move.y = 0;
	old_options.zoom = 1;
	ft_move_points(points, options, move, old_options);
	return (points);
}
