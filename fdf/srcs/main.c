/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:04:17 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 15:27:40 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_options	ft_generate_options(int argc, const char *argv[])
{
	int 		index;
	t_options	options;

	options.window_size = 400;
	options.zoom = 10;
	options.inclination = INCLINATION;
	options.amplifier = HEIGHT_AMPLIFIER;
	if (argc > 2)
	{
		index = 2;
		while (index < argc)
		{
			if (ft_strcmp(argv[index], "-size") == 0)
			{
				options.window_size = ft_atoi(argv[index + 1]);
				++index;
			}
			if (ft_strcmp(argv[index], "-zoom") == 0)
			{
				options.zoom = ft_atoi(argv[index + 1]);
				++index;
			}
			if (ft_strcmp(argv[index], "-amplifier") == 0)
			{
				options.amplifier = ft_atoi(argv[index + 1]);
				++index;
			}
			++index;
		}
	}
	return (options);
}

int 		main(int argc, const char *argv[])
{
	t_options	options;
	t_env		env;

	env.init = 1;
	options = ft_generate_options(argc, argv);
	if (argc < 2)
		ft_putstr("Usage : ./fdf <filename> [-size size]\n");
	else
		ft_display(ft_read(ft_open_file(argv[1]), options), options, env);
	return 0;
}
