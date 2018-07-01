/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/07/01 16:11:37 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_event_key_release(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(env->mlx_id, env->mlx_img);
		mlx_destroy_window(env->mlx_id, env->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int	ft_event_key_press(int keycode, t_env *env)
{
	if (keycode == KEY_RIGHT)
		env->options.x = env->options.x + (0.2 / env->options.zoom);
	else if (keycode == KEY_LEFT)
		env->options.x = env->options.x - (0.2 / env->options.zoom);
	if (keycode == KEY_DOWN)
		env->options.y = env->options.y + (0.2 / env->options.zoom);
	else if (keycode == KEY_UP)
		env->options.y = env->options.y - (0.2 / env->options.zoom);
	else if (keycode == KEY_PLUS)
		env->options.zoom++;
	else if (keycode == KEY_MINUS)
		env->options.zoom--;
	ft_draw(env);
	return (1);
}

int	ft_event_motion(int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	(void)env;
	return (1);
}

