/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/15 16:47:28 by vtouffet         ###   ########.fr       */
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
	mlx_pixel_put(mlx_data.mlx_id, mlx_data.window_id,
				  x + options.window_size / 4,
				  y + options.window_size / 4,
				  color);
}

void	ft_display_line(t_point *point1, t_point *point2, t_mlx mlx_data,
						t_options options)
{
	t_point	diff;
	t_point	inc;
	t_point	pos;
	int 	i;
	//int diff.x, diff.y, i, xinc, yinc, cumul, x, y;
	int color;

	color = 0x00F7F3ED;
	pos.x = point1->x;
	pos.y = point1->y;
	diff.x = abs(point2->x - point1->x);
	diff.y = abs(point2->y - point1->y);
	inc.x = (diff.x > 0) ? 1 : -1;
	inc.y = (diff.y > 0) ? 1 : -1;
	ft_display_point(pos.x, pos.y, mlx_data, options, color);



	cumul = ((diff.x > diff.y) ? diff.x : diff.y) / 2;
	i = 1;
	while (i <= (diff.x > diff.y ? diff.x : diff.y))
	{
		++i;
		if (diff.x > diff.y)
			pos.x += xinc;
		else
			pos.y += yinc;
		cumul += (diff.x > diff.y) ? diff.y : diff.x;
		if (cumul >= (diff.x > diff.y ? diff.x : diff.y))
		{
			cumul -= (diff.x > diff.y) ? diff.x : diff.y;
			if (diff.x > diff.y)
				pos.y += yinc;
			else
				pos.x += xinc;
		}
		ft_display_point(pos.x, pos.y, mlx_data, options, color);
	}
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
