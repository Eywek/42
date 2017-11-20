/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:30:32 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/20 18:33:04 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../includes/fdf.h"

void	ft_start_window(t_env env)
{
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - 130, env.options.height - 80,
					0x00FFFFFF, "> = Increase");
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - 130, env.options.height - 65,
					0x00FFFFFF, "< = Decrease");
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - 130, env.options.height - 40,
					0x00FFFFFF, "+ = Zoom in");
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - 130, env.options.height - 25,
					0x00FFFFFF, "- = Zoom out");
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - (env.options.width - 15),
					env.options.height - 70, 0x00FFFFFF, "RIGHT = Move right");
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - (env.options.width - 15),
					env.options.height - 55, 0x00FFFFFF, "LEFT  = Move left");
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - (env.options.width - 15),
					env.options.height - 40, 0x00FFFFFF, "UP    = Move up");
	mlx_string_put(env.mlx_data.mlx_id, env.mlx_data.window_id,
					env.options.width - (env.options.width - 15),
					env.options.height - 25, 0x00FFFFFF, "DOWN  = Move down");
	mlx_loop(env.mlx_data.mlx_id);
}

void	ft_generate_window(t_env *env)
{
	if (env->options.width <= 0 || env->options.height <= 0 ||
			env->options.width >= 1920 || env->options.height >= 1080)
		ft_throw_error();
	env->mlx_data.mlx_id = mlx_init();
	env->mlx_data.window_id = mlx_new_window(env->mlx_data.mlx_id,
											env->options.width,
											env->options.height,
											WINDOW_TITLE);
	mlx_key_hook(env->mlx_data.window_id, ft_listen_key, env);
	env->init = 1;
}
