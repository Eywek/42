/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:58:36 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 20:00:52 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_handle_arrows(int keycode, t_env *env)
{
	t_point move;

	move.x = 0;
	move.y = 0;
	if (keycode == KEYCODE_RIGHT_ARROW)
		move.x = ARROW_AMPLIFIER;
	else if (keycode == KEYCODE_LEFT_ARROW)
		move.x = -ARROW_AMPLIFIER;
	else if (keycode == KEYCODE_UP_ARROW)
		move.y = -ARROW_AMPLIFIER;
	else if (keycode == KEYCODE_DOWN_ARROW)
		move.y = ARROW_AMPLIFIER;
	if (move.x != 0 || move.y != 0)
	{
		ft_move_points(env->points, env->options, move, env->options.zoom);
		ft_display(env->points, env->options, *env);
	}
}

void	ft_handle_zoom(int keycode, t_env *env)
{
	int		tmp;
	t_point	move;

	move.x = 0;
	move.y = 0;
	if (keycode == KEYCODE_ZOOM_IN)
	{
		tmp = env->options.zoom;
		if (tmp + ZOOM > 100)
			return ;
		env->options.zoom += ZOOM;
		ft_move_points(env->points, env->options, move, tmp);
		ft_display(env->points, env->options, *env);
	}
	else if (keycode == KEYCODE_ZOOM_OUT)
	{
		tmp = env->options.zoom;
		if (tmp - ZOOM <= 0)
			return ;
		env->options.zoom -= ZOOM;
		ft_move_points(env->points, env->options, move, tmp);
		ft_display(env->points, env->options, *env);
	}
}

int		ft_listen_key(int keycode, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (keycode == KEYCODE_ESC)
		exit(0);
	ft_handle_arrows(keycode, env);
	ft_handle_zoom(keycode, env);
	return (0);
}
