/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/15 14:52:23 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "../includes/fdf.h"

void	ft_throw_error(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

void	ft_display_point(int x, int y, t_mlx mlx_data, t_options options, int color)
{
	mlx_pixel_put(mlx_data.mlx_id, mlx_data.window_id, x + options.window_size / 2,
				  (y + (options.window_size / 2)) / sqrt(3), color);
}

void	ft_display_line(t_point *point1, t_point *point2, t_mlx mlx_data,
						t_options options)
{
	/*double a;
	double b;
	int x;
	int y;

	a = (point2->y - point1->y) / (point2->x - point1->x);
	b = point1->y - a * point1->x;
	x = point1->x;
	while (x <= point2->x)
	{
		y = (int)(a * x + b);
		ft_display_point(x, y, mlx_data);
		++x;
	}*/

	int dx, dy, i, xinc, yinc, cumul, x, y;
	x = point1->x;
	y = point1->y;
	dx = point2->x - point1->x;
	dy = point2->y - point1->y;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	ft_display_point(x, y, mlx_data, options, 0x002ECC71);
	if (dx > dy)
	{
		cumul = dx / 2;
		i = 1;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			ft_display_point(x, y, mlx_data, options, 0x003498DB);
			++i;
		}
	}
	else
	{
		cumul = dy / 2;
		i = 1;
		while (i < dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			ft_display_point(x, y, mlx_data, options, 0x00E67E22);
			++i;
		}
	}


/*
	t_point p = *point1;
	t_point p1 = *point2;
	t_point		d;
	t_point		s;
	int			err;
	int			e2;

	d.x = abs((p1.x - p.x));
	d.y = abs((p1.y - p.y));
	s.x = (p.x < p1.x ? 1 : -1);
	s.y = (p.y < p1.y ? 1 : -1);
	err = d.x - d.y;
	while (p.x != p1.x || p.y != p1.y)
	{
		ft_display_point(p.x, p.y, mlx_data, options);
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			p.x += s.x;
		}
		if (e2 < d.x)
		{
			err += d.x;
			p.y += s.y;
		}
	}
*/
}

t_mlx	ft_generate_window(t_options options)
{
	t_mlx	mlx_data;

	mlx_data.mlx_id = mlx_init();
	mlx_data.window_id = mlx_new_window(mlx_data.mlx_id, options.window_size,
										options.window_size, WINDOW_TITLE);
	mlx_data.options = options;
	mlx_key_hook(mlx_data.window_id, ft_listen_key, &mlx_data);
	return (mlx_data);
}

t_point	*ft_get_next_line(t_list *points)
{
	t_point	*point;
	int 	tmp_index;
	int 	tmp_x;

	tmp_index = ((t_point*)(points->content))->index;
	tmp_x = ((t_point*)(points->content))->x;

	ft_putstr("SEARCH FOR index = ");
	ft_putnbr(tmp_index + 1);
	ft_putstr(" AND x = ");
	ft_putnbr(tmp_x);
	ft_putstr("\n");

	while (points)
	{
		point = (t_point*)(points->content);
		if (point->index == tmp_index + 1 && point->x == tmp_x)
			return (point);
		points = points->next;
	}
	return (NULL);
}

void	ft_display(t_list *points,  t_options options)
{
	t_mlx	mlx_data;
	t_point	*point1;
	t_point	*point2;
	t_point	*next_line;

	ft_putstr("DEBUG OF ");
	ft_putnbr(ft_lstcount(points));
	ft_putstr(" POINTS:\n");
	ft_lstmap(points, &ft_debug_points);
	mlx_data = ft_generate_window(options);
	while (points && points->next)
	{
		point1 = (t_point*)(points->content);
		point2 = (t_point*)(points->next->content);
		if (point1->index == point2->index)
			ft_display_line(point1, point2, mlx_data, options);

		next_line = ft_get_next_line(points);
		if (next_line)
			ft_display_line(point1, next_line, mlx_data, options);

		points = points->next;
	}
	if (points)
		ft_display_point(((t_point*)(points->content))->x, ((t_point*)(points->content))->y, mlx_data, options, 0x002ECC71);
	mlx_loop(mlx_data.mlx_id);
}
