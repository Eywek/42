/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:58:36 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 16:32:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_list	*ft_zoom(t_env *env, int old_zoom)
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
		point->h /= env->options.amplifier;
		ptr->content = ft_new_point(point->x, point->y, point->h, env->options);
		free(point);
		ptr = ptr->next;
	}
	return (points);
}

t_list	*ft_rewrite_points(t_env *env, int x, int y)
{
	t_list	*ptr;
	t_list	*points;
	t_point	*point;

	points = env->points;
	ptr = points;
	while (ptr)
	{
		point = ptr->content;
		point->x = point->x / env->options.zoom;
		point->y = (point->y + point->h) / env->options.zoom;
		point->h /= env->options.amplifier;
		ptr->content = ft_new_point(point->x + x, point->y + y, point->h,
									env->options);
		free(point);
		ptr = ptr->next;
	}
	return (points);
}

void	ft_handle_arrows(int keycode, t_env *env)
{
	if (keycode == KEYCODE_RIGHT_ARROW)
		ft_display(ft_rewrite_points(env, ARROW_AMPLIFIER, 0),
					env->options, *env);
	else if (keycode == KEYCODE_LEFT_ARROW)
		ft_display(ft_rewrite_points(env, -ARROW_AMPLIFIER, 0),
					env->options, *env);
	else if (keycode == KEYCODE_UP_ARROW)
		ft_display(ft_rewrite_points(env, 0, -ARROW_AMPLIFIER),
					env->options, *env);
	else if (keycode == KEYCODE_DOWN_ARROW)
		ft_display(ft_rewrite_points(env, 0, ARROW_AMPLIFIER),
					env->options, *env);
}

int		ft_listen_key(int keycode, void *param)
{
	t_env	*env;
	int		tmp;

	env = (t_env*)param;
	if (keycode == KEYCODE_ESC)
		exit(0);
	if (keycode == KEYCODE_ZOOM_IN)
	{
		tmp = env->options.zoom;
		if (tmp + ZOOM > 100)
			return (0);
		env->options.zoom += ZOOM;
		ft_display(ft_zoom(env, tmp), env->options, *env);
	}
	else if (keycode == KEYCODE_ZOOM_OUT)
	{
		tmp = env->options.zoom;
		if (tmp - ZOOM <= 0)
			return (0);
		env->options.zoom -= ZOOM;
		ft_display(ft_zoom(env, tmp), env->options, *env);
	}
	else
		ft_handle_arrows(keycode, env);
	return (0);
}
