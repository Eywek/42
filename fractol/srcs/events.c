/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/23 14:30:46 by valentin         ###   ########.fr       */
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
	(void)keycode;
	(void)env;
	return (1);
}

int	ft_event_motion(int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	(void)env;
	return (1);
}

