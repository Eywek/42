/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:58:36 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 15:25:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../includes/fdf.h"

int ft_listen_key(int keycode, void *param)
{
	t_mlx	*mlx_data;

	mlx_data = param;
	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(mlx_data->mlx_id, mlx_data->window_id);
		exit(0);
	}
	return (0);
}
