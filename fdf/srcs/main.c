/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:04:17 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/20 13:15:15 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf.h"

t_options	ft_generate_options(int argc, const char *argv[])
{
	int			index;
	t_options	options;

	options.width = WINDOW_WIDTH;
	options.height = WINDOW_HEIGHT;
	options.zoom = 10;
	options.inclination = INCLINATION;
	options.amplifier = HEIGHT_AMPLIFIER;
	if (argc > 2)
	{
		index = 2;
		while (index < argc)
		{
			if (ft_strcmp(argv[index], "-width") == 0 && index + 1 < argc)
				options.width = ft_atoi(argv[++index]);
			if (ft_strcmp(argv[index], "-height") == 0 && index + 1 < argc)
				options.height = ft_atoi(argv[++index]);
			if (ft_strcmp(argv[index], "-zoom") == 0 && index + 1 < argc)
				options.zoom = ft_atoi(argv[++index]);
			if (ft_strcmp(argv[index], "-amplifier") == 0 && index + 1 < argc)
				options.amplifier = ft_atoi(argv[++index]);
			++index;
		}
	}
	if (options.amplifier <= 0)
		options.amplifier = 1;
	if (options.zoom <= 0)
		options.zoom = 1;
	return (options);
}

int			ft_open_file(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

int			main(int argc, const char *argv[])
{
	t_options	options;
	t_env		env;

	env.init = 0;
	options = ft_generate_options(argc, argv);
	if (argc < 2)
		ft_putstr("Usage : ./fdf <filename> [-width width] [-height height] "
						"[-zoom zoom] [-amplifier amplifier]\n");
	else
		ft_display(ft_read(ft_open_file(argv[1]), options, options), options,
				env);
	return (0);
}
