/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/20 10:23:45 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "../includes/fdf.h"

void	ft_display_point(int x, int y, t_env env, int color)
{
	mlx_pixel_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
				x + env.options.width / 2,
				(y + env.options.height / 2) / env.options.inclination,
				color);
}

void	ft_start_display_line(t_point *point1, t_point *point2, t_display inf,
								t_env env)
{
	inf.error = ((inf.diff.x > inf.diff.y) ? inf.diff.x : inf.diff.y) / 2;
	inf.i = 1;
	while (inf.i <= (inf.diff.x > inf.diff.y ? inf.diff.x : inf.diff.y))
	{
		++inf.i;
		if (inf.diff.x > inf.diff.y)
			inf.pos.x += inf.inc.x;
		else
			inf.pos.y += inf.inc.y;
		inf.error += (inf.diff.x > inf.diff.y) ? inf.diff.y : inf.diff.x;
		if (inf.error >= (inf.diff.x > inf.diff.y ? inf.diff.x : inf.diff.y))
		{
			inf.error -= (inf.diff.x > inf.diff.y) ? inf.diff.x : inf.diff.y;
			if (inf.diff.x > inf.diff.y)
				inf.pos.y += inf.inc.y;
			else
				inf.pos.x += inf.inc.x;
		}
		if (point1->h > 0 && point2->h > 0)
			ft_display_point(inf.pos.x, inf.pos.y, env, MAX_COLOR);
		else if (point2->h > 0 || point1->h > 0)
			ft_display_point(inf.pos.x, inf.pos.y, env, MID_COLOR);
		else
			ft_display_point(inf.pos.x, inf.pos.y, env, DEFAULT_COLOR);
	}
}

void	ft_display_line(t_point *point1, t_point *point2, t_env env)
{
	t_display infos;

	infos.pos.x = point1->x;
	infos.pos.y = point1->y;
	infos.diff.x = abs(point2->x - point1->x);
	infos.diff.y = abs(point2->y - point1->y);
	infos.inc.x = (point2->x - point1->x > 0) ? 1 : -1;
	infos.inc.y = (point2->y - point1->y > 0) ? 1 : -1;
	if (point1->h > 0)
		ft_display_point(infos.pos.x, infos.pos.y, env, MAX_COLOR);
	else
		ft_display_point(infos.pos.x, infos.pos.y, env, DEFAULT_COLOR);
	ft_start_display_line(point1, point2, infos, env);
}

t_point	*ft_get_next_line(t_list *points)
{
	t_point		*point;
	int			x_searched;
	int			current_index;

	x_searched = ((t_point*)(points->content))->x;
	current_index = ((t_point*)(points->content))->index;
	while (points && points->next)
	{
		point = points->next->content;
		if (point->x == x_searched || current_index + 1 < point->index)
			return (points->content);
		if (points->next->next == NULL && current_index + 1 == point->index)
			return (points->next->content);
		points = points->next;
	}
	return (NULL);
}

void	ft_display(t_list *points, t_options options, t_env env)
{
	t_point	*point1;
	t_point	*point2;
	t_point	*next_line;

	env.options = options;
	env.points = points;
	if (!env.init)
		ft_generate_window(&env);
	else
		mlx_clear_window(env.mlx_data.mlx_id, env.mlx_data.window_id);
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
	ft_start_window(env);
}
