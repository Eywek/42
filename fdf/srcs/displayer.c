/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 15:24:27 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "stdio.h"
#include "../includes/fdf.h"

void	ft_throw_error(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

t_list	*ft_display_line(t_list *line)
{
	int i = 0;
	char **content = ((t_line*)(line->content))->content;
	while (content[i])
		ft_putstr(content[i++]);
	ft_putchar('\n');
	return (line);
}

void	ft_display(t_list *lines,  t_options options)
{
	t_mlx	mlx_data;

	mlx_data.mlx_id = mlx_init();
	mlx_data.window_id = mlx_new_window(mlx_data.mlx_id, options.window_size,
										options.window_size, WINDOW_TITLE);
	mlx_data.options = options;
	mlx_key_hook(mlx_data.window_id, ft_listen_key, &mlx_data);
	mlx_loop(mlx_data.mlx_id);


	ft_lstmap(lines, &ft_display_line);
}
