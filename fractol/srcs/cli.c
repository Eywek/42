/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/23 13:44:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_fractal	g_fractals[FRACTALS_COUNT] =
{
	{"julia", ft_julia, 0, 0, 0, 0, 0, 0, 0},
    {"mandelbrot", ft_mandelbrot, 0, 0, 0, 0, 0, 0, 0},
	{"burningship", ft_burningship, 0, 0, 0, 0, 0, 0, 0}
};

int		ft_handle_fractal(char *fractal)
{
	int	i;

	if (!fractal)
		return (0);
	i = -1;
	while (++i < FRACTALS_COUNT)
		if (ft_strcmp(g_fractals[i].name, fractal) == 0)
		{
			ft_init(g_fractals[i]);
			return (1);
		}
	return (0);
}

int		main(int argc, char *argv[])
{
	if (argc != 2 || !ft_handle_fractal(argv[1]))
		write(STDIN_FILENO, FRACTOL_USAGE, sizeof(FRACTOL_USAGE));
	return (0);
}
