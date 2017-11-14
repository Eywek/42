/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 18:29:53 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../includes/fdf.h"

void	ft_throw_error(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

void	ft_display_line(t_list *line, int y, t_mlx mlx_data, int padding)
{
	int x;
	char **content;

	content = ((t_line*)(line->content))->content;
	x = 1;
	while (content[x] != 0)
	{
		mlx_pixel_put(mlx_data.mlx_id, mlx_data.window_id, x * padding,
					  y * padding, 0x00FFFFFF);
		++x;
	}
}

t_mlx	ft_generate_window(t_options options)
{
	t_mlx	mlx_data;

	mlx_data.mlx_id = mlx_init();
	mlx_data.window_id = mlx_new_window(mlx_data.mlx_id, options.window_size,
										options.window_size, WINDOW_TITLE);
	mlx_data.options = options;
	mlx_key_hook(mlx_data.window_id, ft_listen_key, &mlx_data);
	return (mlx_data);
}


void	ft_display(t_list *lines,  t_options options)
{
	t_mlx	mlx_data;
	int 	y;
	int 	padding;

	mlx_data = ft_generate_window(options);
	y = 1;
	padding = mlx_data.options.window_size / (ft_lstcount(lines) + 1);
	while (lines)
	{
		ft_display_line(lines, y++, mlx_data, padding);
		lines = lines->next;
	}
	mlx_loop(mlx_data.mlx_id);
}
