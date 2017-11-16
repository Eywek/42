/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:58:36 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 11:55:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_list	*ft_rewrite_points(t_env *env, int old_zoom)
{
	t_list	*ptr;
	t_list	*points;
	t_point	*point;

	points = env->points;
	ptr = points;
	while (ptr)
	{
		point = ptr->content;
		point->x = point->x / old_zoom;
		point->y = (point->y + point->h) / old_zoom;
		ptr->content = ft_new_point(point->x, point->y, point->h, env->options);
		ptr = ptr->next;
	}
	return (points);
}

int 	ft_listen_key(int keycode, void *param)
{
	t_env		*env;
	int 		tmp;

	env = (t_env*)param;
	if (keycode == KEYCODE_ESC)
		exit(0);
	if (keycode == KEYCODE_ZOOM_IN)
	{
		tmp = env->options.zoom;
		if (tmp + 10 > 100)
			return (0);
		env->options.zoom += 10;
		ft_display(ft_rewrite_points(env, tmp), env->options, *env);
	}
	else if (keycode == KEYCODE_ZOOM_OUT)
	{
		tmp = env->options.zoom;
		if (tmp - 10 <= 0)
			return (0);
		env->options.zoom -= 10;
		ft_display(ft_rewrite_points(env, tmp), env->options, *env);
	}
	return (0);
}
