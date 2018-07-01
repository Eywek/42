/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/07/01 15:55:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_init(t_fractal fractal)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(env));
	env.options.zoom = 1;
	env.options.iterations = 300;
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

void	ft_putpixel(t_env *env, int x, int y, t_color color)
{
	int		pos;
	char	*img;

	pos = (env->bpp / 8) * x;
	if (y)
		pos += y * env->size;
	img = env->image;
	img[pos] = (char)color.red; // Red
	img[pos + 1] = (char)color.green; // Green
	img[pos + 2] = (char)color.blue; // Blue
}
