/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/17 17:08:44 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../includes/fdf.h"

void	ft_display_point(int x, int y, t_env env, int color)
{
	mlx_pixel_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
				x + env.options.width / 2,
				(y + env.options.height / 2) / env.options.inclination,
				color);
}

void	ft_display_line(t_point *point1, t_point *point2, t_env env)
{
	t_point	diff; // difference entre les deux points
	t_point	inc;
	t_point	pos; // position du point a placer
	int		i;
	int		cumul;

	pos.x = point1->x;
	pos.y = point1->y;
	diff.x = abs(point2->x - point1->x); // diff entre les x
	diff.y = abs(point2->y - point1->y); // diff entre les y
	inc.x = (point2->x - point1->x > 0) ? 1 : -1; // si point 2 plus haut que point 1 en x --> inc.x = 1 sinon - 1
	inc.y = (point2->y - point1->y > 0) ? 1 : -1; // si point 2 plus bas en ligne que point 1 --> inc.y = 1 sinon -1
	if (point1->h > 0) // selon la couleur
		ft_display_point(pos.x, pos.y, env, MAX_COLOR);
	else
		ft_display_point(pos.x, pos.y, env, DEFAULT_COLOR);
	cumul = ((diff.x > diff.y) ? diff.x : diff.y) / 2; // si le point est trace en x ou en y, cumul = diff / 2
	i = 1;
	while (i <= (diff.x > diff.y ? diff.x : diff.y)) // tracer le nb de points manquant selon la diff
	{
		++i;
		if (diff.x > diff.y) // on increment la pos selon si c'est en x ou en y
			pos.x += inc.x;
		else
			pos.y += inc.y;
		cumul += (diff.x > diff.y) ? diff.y : diff.x; // on ajoute la diff
		if (cumul >= (diff.x > diff.y ? diff.x : diff.y)) // si c'est superieur a la diff on remove une fois la diff et on incremente la pos
		{
			cumul -= (diff.x > diff.y) ? diff.x : diff.y;
			if (diff.x > diff.y)
				pos.y += inc.y;
			else
				pos.x += inc.x;
		}
		if (point1->h > 0 && point2->h > 0) // on affiche
			ft_display_point(pos.x, pos.y, env, MAX_COLOR);
		else if (point2->h > 0 || point1->h > 0)
			ft_display_point(pos.x, pos.y, env, MID_COLOR);
		else
			ft_display_point(pos.x, pos.y, env, DEFAULT_COLOR);
	}
}

t_point	*ft_get_next_line(t_list *points)
{
	t_point		*point;
	int 		x_searched;
	int 		current_index;

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
