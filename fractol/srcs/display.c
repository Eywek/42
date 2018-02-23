/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/23 14:39:04 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_init(t_fractal fractal)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(env));
	env.fractal = fractal.f;
	env.mlx_id = mlx_init();
	env.mlx_win = mlx_new_window(env.mlx_id, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	mlx_hook(env.mlx_win, KEYRELEASE, KEYRELEASEMASK, ft_event_key_release, &env);
	mlx_hook(env.mlx_win, KEYPRESS, KEYPRESSMASK, ft_event_key_press, &env);
	mlx_hook(env.mlx_win, MOTIONNOTIFY, POINTERMOTIONMASK, ft_event_motion, &env);
	ft_draw(&env);
	mlx_loop(env.mlx_id);
}

void	ft_draw(t_env *env)
{
	if (env->mlx_img)
		mlx_destroy_image(env->mlx_id, env->mlx_img);
	env->mlx_img = mlx_new_image(env->mlx_id, WIN_WIDTH, WIN_HEIGHT);
	env->image = mlx_get_data_addr(env->mlx_img, &env->bpp,
									&env->size, &env->endian);
	env->fractal(env);
	mlx_put_image_to_window(env->mlx_id, env->mlx_win, env->mlx_img, 0, 0);
}

void	ft_putpixel(t_env *env, int x, int y, int color)
{
	if (y >= WIN_HEIGHT || x >= WIN_WIDTH || x < 0 || y < 0)
		return ;
	*(int *)&env->image[(y * env->size) + (x * (env->bpp / 8))] = color;
}
