/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 13:32:16 by vtouffet         ###   ########.fr       */
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

void	ft_display_point(int x, int y, t_env env, int color)
{
	y += x * .5;
	x -= y * .3;
	mlx_pixel_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
				  x + env.options.window_size / 2,
				  (y + env.options.window_size / 2) / env.options.inclination,
				  color);
}

void	ft_display_line(t_point *point1, t_point *point2, t_env env)
{
	t_point	diff;
	t_point	inc;
	t_point	pos;
	int 	i;
	int 	cumul;

	pos.x = point1->x;
	pos.y = point1->y;
	diff.x = abs(point2->x - point1->x);
	diff.y = abs(point2->y - point1->y);
	inc.x = (point2->x - point1->x > 0) ? 1 : -1;
	inc.y = (point2->y - point1->y > 0) ? 1 : -1;
	ft_display_point(pos.x, pos.y, env, 0x00F7F3ED);
	cumul = ((diff.x > diff.y) ? diff.x : diff.y) / 2;
	i = 1;
	while (i <= (diff.x > diff.y ? diff.x : diff.y))
	{
		++i;
		if (diff.x > diff.y)
			pos.x += inc.x;
		else
			pos.y += inc.y;
		cumul += (diff.x > diff.y) ? diff.y : diff.x;
		if (cumul >= (diff.x > diff.y ? diff.x : diff.y))
		{
			cumul -= (diff.x > diff.y) ? diff.x : diff.y;
			if (diff.x > diff.y)
				pos.y += inc.y;
			else
				pos.x += inc.x;
		}
		//if (pos.y + point1->h != point1->y && diff.x > diff.y)
		//	ft_display_point(pos.x, pos.y, env, 0x00E01F11);
		//else
			ft_display_point(pos.x, pos.y, env, 0x00F7F3ED);
	}
}

void	ft_generate_window(t_env *env)
{
	env->mlx_data.mlx_id = mlx_init();
	env->mlx_data.window_id = mlx_new_window(env->mlx_data.mlx_id,
											 env->options.window_size,
											 env->options.window_size,
										WINDOW_TITLE);
	mlx_key_hook(env->mlx_data.window_id, ft_listen_key, env);
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

void	ft_display(t_list *points,  t_options options, t_env env)
{
	t_point	*point1;
	t_point	*point2;
	t_point	*next_line;

	ft_putstr("DEBUG OF ");
	ft_putnbr(ft_lstcount(points));
	ft_putstr(" POINTS:\n");
	ft_lstmap(points, &ft_debug_points);


	env.options = options;
	env.points = points;
	if (env.init)
		ft_generate_window(&env);
	else
		mlx_clear_window(env.mlx_data.mlx_id, env.mlx_data.window_id);
	env.init = 0;
	while (points && points->next)
	{
		point1 = (t_point*)(points->content);
		point2 = (t_point*)(points->next->content);
		if (point1->index == point2->index)
			ft_display_line(point1, point2, env);

		next_line = ft_get_next_line(points);
		if (next_line)
			ft_display_line(point1, next_line, env);

		points = points->next;
	}
	if (points)
		ft_display_point(((t_point*)(points->content))->x,
						 ((t_point*)(points->content))->y, env, 0x00F7F3ED);
	mlx_loop(env.mlx_data.mlx_id);
}
